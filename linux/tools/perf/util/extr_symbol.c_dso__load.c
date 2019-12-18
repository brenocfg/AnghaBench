#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct symsrc {int dummy; } ;
struct nscookie {int dummy; } ;
struct map {TYPE_1__* groups; } ;
struct machine {char* root_dir; } ;
struct dso {char* long_name; scalar_t__ kernel; scalar_t__ symtab_type; int /*<<< orphan*/  lock; int /*<<< orphan*/  name; scalar_t__ symsrc_filename; scalar_t__ nsinfo; int /*<<< orphan*/  has_build_id; scalar_t__ adjust_symbols; } ;
typedef  int /*<<< orphan*/  newmapname ;
typedef  enum dso_binary_type { ____Placeholder_dso_binary_type } dso_binary_type ;
struct TYPE_2__ {struct machine* machine; } ;

/* Variables and functions */
 int BUILD_ID_SIZE ; 
 int DSO_BINARY_TYPE__BUILD_ID_CACHE ; 
 int DSO_BINARY_TYPE__BUILD_ID_CACHE_DEBUGINFO ; 
 scalar_t__ DSO_BINARY_TYPE__GUEST_KMODULE ; 
 scalar_t__ DSO_BINARY_TYPE__GUEST_KMODULE_COMP ; 
 scalar_t__ DSO_BINARY_TYPE__JAVA_JIT ; 
 scalar_t__ DSO_BINARY_TYPE__NOT_FOUND ; 
 size_t DSO_BINARY_TYPE__SYMTAB_CNT ; 
 scalar_t__ DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE ; 
 scalar_t__ DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE_COMP ; 
 scalar_t__ DSO_TYPE_GUEST_KERNEL ; 
 scalar_t__ DSO_TYPE_KERNEL ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  __symbol__join_symfs (char*,int,char*) ; 
 int* binary_type_symtab ; 
 scalar_t__ dso__find_perf_map (char*,int,scalar_t__*) ; 
 int /*<<< orphan*/  dso__is_compatible_symtab_type (struct dso*,int,int) ; 
 int dso__load_guest_kernel_sym (struct dso*,struct map*) ; 
 int dso__load_kernel_sym (struct dso*,struct map*) ; 
 int dso__load_perf_map (char const*,struct dso*) ; 
 int dso__load_sym (struct dso*,struct map*,struct symsrc*,struct symsrc*,int) ; 
 scalar_t__ dso__loaded (struct dso*) ; 
 scalar_t__ dso__read_binary_type_filename (struct dso*,int,char*,char*,int) ; 
 int /*<<< orphan*/  dso__set_build_id (struct dso*,unsigned char*) ; 
 int /*<<< orphan*/  dso__set_loaded (struct dso*) ; 
 int dso__synthesize_plt_symbols (struct dso*,struct symsrc*) ; 
 scalar_t__ filename__read_build_id (char*,unsigned char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int is_regular_file (char*) ; 
 scalar_t__ machine__is (struct machine*,char*) ; 
 int /*<<< orphan*/  machine__map_x86_64_entry_trampolines (struct machine*,struct dso*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  nsinfo__mountns_enter (scalar_t__,struct nscookie*) ; 
 int /*<<< orphan*/  nsinfo__mountns_exit (struct nscookie*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strdup (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  symsrc__destroy (struct symsrc*) ; 
 scalar_t__ symsrc__has_symtab (struct symsrc*) ; 
 int symsrc__init (struct symsrc*,struct dso*,char*,int) ; 
 scalar_t__ symsrc__possibly_runtime (struct symsrc*) ; 

int dso__load(struct dso *dso, struct map *map)
{
	char *name;
	int ret = -1;
	u_int i;
	struct machine *machine;
	char *root_dir = (char *) "";
	int ss_pos = 0;
	struct symsrc ss_[2];
	struct symsrc *syms_ss = NULL, *runtime_ss = NULL;
	bool kmod;
	bool perfmap;
	unsigned char build_id[BUILD_ID_SIZE];
	struct nscookie nsc;
	char newmapname[PATH_MAX];
	const char *map_path = dso->long_name;

	perfmap = strncmp(dso->name, "/tmp/perf-", 10) == 0;
	if (perfmap) {
		if (dso->nsinfo && (dso__find_perf_map(newmapname,
		    sizeof(newmapname), &dso->nsinfo) == 0)) {
			map_path = newmapname;
		}
	}

	nsinfo__mountns_enter(dso->nsinfo, &nsc);
	pthread_mutex_lock(&dso->lock);

	/* check again under the dso->lock */
	if (dso__loaded(dso)) {
		ret = 1;
		goto out;
	}

	if (map->groups && map->groups->machine)
		machine = map->groups->machine;
	else
		machine = NULL;

	if (dso->kernel) {
		if (dso->kernel == DSO_TYPE_KERNEL)
			ret = dso__load_kernel_sym(dso, map);
		else if (dso->kernel == DSO_TYPE_GUEST_KERNEL)
			ret = dso__load_guest_kernel_sym(dso, map);

		if (machine__is(machine, "x86_64"))
			machine__map_x86_64_entry_trampolines(machine, dso);
		goto out;
	}

	dso->adjust_symbols = 0;

	if (perfmap) {
		ret = dso__load_perf_map(map_path, dso);
		dso->symtab_type = ret > 0 ? DSO_BINARY_TYPE__JAVA_JIT :
					     DSO_BINARY_TYPE__NOT_FOUND;
		goto out;
	}

	if (machine)
		root_dir = machine->root_dir;

	name = malloc(PATH_MAX);
	if (!name)
		goto out;

	kmod = dso->symtab_type == DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE ||
		dso->symtab_type == DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE_COMP ||
		dso->symtab_type == DSO_BINARY_TYPE__GUEST_KMODULE ||
		dso->symtab_type == DSO_BINARY_TYPE__GUEST_KMODULE_COMP;


	/*
	 * Read the build id if possible. This is required for
	 * DSO_BINARY_TYPE__BUILDID_DEBUGINFO to work
	 */
	if (!dso->has_build_id &&
	    is_regular_file(dso->long_name)) {
	    __symbol__join_symfs(name, PATH_MAX, dso->long_name);
	    if (filename__read_build_id(name, build_id, BUILD_ID_SIZE) > 0)
		dso__set_build_id(dso, build_id);
	}

	/*
	 * Iterate over candidate debug images.
	 * Keep track of "interesting" ones (those which have a symtab, dynsym,
	 * and/or opd section) for processing.
	 */
	for (i = 0; i < DSO_BINARY_TYPE__SYMTAB_CNT; i++) {
		struct symsrc *ss = &ss_[ss_pos];
		bool next_slot = false;
		bool is_reg;
		bool nsexit;
		int sirc = -1;

		enum dso_binary_type symtab_type = binary_type_symtab[i];

		nsexit = (symtab_type == DSO_BINARY_TYPE__BUILD_ID_CACHE ||
		    symtab_type == DSO_BINARY_TYPE__BUILD_ID_CACHE_DEBUGINFO);

		if (!dso__is_compatible_symtab_type(dso, kmod, symtab_type))
			continue;

		if (dso__read_binary_type_filename(dso, symtab_type,
						   root_dir, name, PATH_MAX))
			continue;

		if (nsexit)
			nsinfo__mountns_exit(&nsc);

		is_reg = is_regular_file(name);
		if (is_reg)
			sirc = symsrc__init(ss, dso, name, symtab_type);

		if (nsexit)
			nsinfo__mountns_enter(dso->nsinfo, &nsc);

		if (!is_reg || sirc < 0)
			continue;

		if (!syms_ss && symsrc__has_symtab(ss)) {
			syms_ss = ss;
			next_slot = true;
			if (!dso->symsrc_filename)
				dso->symsrc_filename = strdup(name);
		}

		if (!runtime_ss && symsrc__possibly_runtime(ss)) {
			runtime_ss = ss;
			next_slot = true;
		}

		if (next_slot) {
			ss_pos++;

			if (syms_ss && runtime_ss)
				break;
		} else {
			symsrc__destroy(ss);
		}

	}

	if (!runtime_ss && !syms_ss)
		goto out_free;

	if (runtime_ss && !syms_ss) {
		syms_ss = runtime_ss;
	}

	/* We'll have to hope for the best */
	if (!runtime_ss && syms_ss)
		runtime_ss = syms_ss;

	if (syms_ss)
		ret = dso__load_sym(dso, map, syms_ss, runtime_ss, kmod);
	else
		ret = -1;

	if (ret > 0) {
		int nr_plt;

		nr_plt = dso__synthesize_plt_symbols(dso, runtime_ss);
		if (nr_plt > 0)
			ret += nr_plt;
	}

	for (; ss_pos > 0; ss_pos--)
		symsrc__destroy(&ss_[ss_pos - 1]);
out_free:
	free(name);
	if (ret < 0 && strstr(dso->name, " (deleted)") != NULL)
		ret = 0;
out:
	dso__set_loaded(dso);
	pthread_mutex_unlock(&dso->lock);
	nsinfo__mountns_exit(&nsc);

	return ret;
}