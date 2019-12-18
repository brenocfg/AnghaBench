#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct map {int dummy; } ;
struct dso {int /*<<< orphan*/  build_id; int /*<<< orphan*/  has_build_id; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  host_build_id ;

/* Variables and functions */
 int BUILD_ID_SIZE ; 
 int /*<<< orphan*/  DSO__NAME_KCORE ; 
 int PATH_MAX ; 
 int SBUILD_ID_SIZE ; 
 int /*<<< orphan*/  build_id__sprintf (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  build_id_cache__kallsyms_path (char*,char*,int) ; 
 int /*<<< orphan*/  buildid_dir ; 
 int dso__build_id_equal (struct dso*,int /*<<< orphan*/ *) ; 
 scalar_t__ filename__readable (char*) ; 
 int /*<<< orphan*/  find_matching_kcore (struct map*,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* strdup (char*) ; 
 scalar_t__ sysfs__read_build_id (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  validate_kcore_addresses (char*,struct map*) ; 

__attribute__((used)) static char *dso__find_kallsyms(struct dso *dso, struct map *map)
{
	u8 host_build_id[BUILD_ID_SIZE];
	char sbuild_id[SBUILD_ID_SIZE];
	bool is_host = false;
	char path[PATH_MAX];

	if (!dso->has_build_id) {
		/*
		 * Last resort, if we don't have a build-id and couldn't find
		 * any vmlinux file, try the running kernel kallsyms table.
		 */
		goto proc_kallsyms;
	}

	if (sysfs__read_build_id("/sys/kernel/notes", host_build_id,
				 sizeof(host_build_id)) == 0)
		is_host = dso__build_id_equal(dso, host_build_id);

	/* Try a fast path for /proc/kallsyms if possible */
	if (is_host) {
		/*
		 * Do not check the build-id cache, unless we know we cannot use
		 * /proc/kcore or module maps don't match to /proc/kallsyms.
		 * To check readability of /proc/kcore, do not use access(R_OK)
		 * since /proc/kcore requires CAP_SYS_RAWIO to read and access
		 * can't check it.
		 */
		if (filename__readable("/proc/kcore") &&
		    !validate_kcore_addresses("/proc/kallsyms", map))
			goto proc_kallsyms;
	}

	build_id__sprintf(dso->build_id, sizeof(dso->build_id), sbuild_id);

	/* Find kallsyms in build-id cache with kcore */
	scnprintf(path, sizeof(path), "%s/%s/%s",
		  buildid_dir, DSO__NAME_KCORE, sbuild_id);

	if (!find_matching_kcore(map, path, sizeof(path)))
		return strdup(path);

	/* Use current /proc/kallsyms if possible */
	if (is_host) {
proc_kallsyms:
		return strdup("/proc/kallsyms");
	}

	/* Finally, find a cache of kallsyms */
	if (!build_id_cache__kallsyms_path(sbuild_id, path, sizeof(path))) {
		pr_err("No kallsyms or vmlinux with build-id %s was found\n",
		       sbuild_id);
		return NULL;
	}

	return strdup(path);
}