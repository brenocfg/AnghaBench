#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_17__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_33__ {int /*<<< orphan*/  file; } ;
struct TYPE_32__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  arch; } ;
struct TYPE_31__ {TYPE_6__* info; } ;
struct TYPE_30__ {int xtr_idx; } ;
struct TYPE_29__ {char* name; } ;
struct TYPE_28__ {TYPE_17__* bin; int /*<<< orphan*/  config; int /*<<< orphan*/  io; int /*<<< orphan*/  dbg; } ;
struct TYPE_27__ {int fd; } ;
struct TYPE_26__ {void* maxstrbuf; void* minstrlen; } ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  TYPE_1__ RCoreFile ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RBinPlugin ;
typedef  TYPE_4__ RBinOptions ;
typedef  TYPE_5__ RBinObject ;
typedef  TYPE_6__ RBinInfo ;
typedef  TYPE_7__ RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  UT64_MAX ; 
 int /*<<< orphan*/  eprintf (char*,char const*) ; 
 int /*<<< orphan*/  get_base_from_maps (TYPE_2__*,char const*) ; 
 TYPE_7__* r_bin_cur (TYPE_17__*) ; 
 TYPE_5__* r_bin_cur_object (TYPE_17__*) ; 
 TYPE_3__* r_bin_file_cur_plugin (TYPE_7__*) ; 
 int /*<<< orphan*/  r_bin_open (TYPE_17__*,char const*,TYPE_4__*) ; 
 int /*<<< orphan*/  r_bin_options_init (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__* r_config_get (int /*<<< orphan*/ ,char*) ; 
 void* r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_bin_set_arch_bits (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_bin_set_env (TYPE_2__*,TYPE_7__*) ; 
 int /*<<< orphan*/  r_core_cmd0 (TYPE_2__*,char*) ; 
 TYPE_1__* r_core_file_cur (TYPE_2__*) ; 
 int /*<<< orphan*/  r_debug_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_io_desc_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_io_fd_get_pid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_io_fd_get_tid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setbpint (TYPE_2__*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

__attribute__((used)) static int r_core_file_do_load_for_debug(RCore *r, ut64 baseaddr, const char *filenameuri) {
	RCoreFile *cf = r_core_file_cur (r);
	RIODesc *desc = cf ? r_io_desc_get (r->io, cf->fd) : NULL;
	RBinFile *binfile = NULL;
	RBinPlugin *plugin;
	int xtr_idx = 0; // if 0, load all if xtr is used

	// TODO : Honor file.path eval var too?
	if (!strncmp ("dbg://", filenameuri, 6)) {
		filenameuri += 6;
	}
	if (!desc) {
		return false;
	}
	if (cf) {
		r_debug_select (r->dbg, r_io_fd_get_pid (r->io, cf->fd),
				r_io_fd_get_tid (r->io, cf->fd));
	}
#if !__linux__
#if !__WINDOWS__
	baseaddr = get_base_from_maps (r, filenameuri);
#endif
	if (baseaddr != UT64_MAX) {
		r_config_set_i (r->config, "bin.baddr", baseaddr);
	}
#endif
	int fd = cf? cf->fd: -1;
	RBinOptions opt;
	r_bin_options_init (&opt, fd, baseaddr, UT64_MAX, false);
	opt.xtr_idx = xtr_idx;
	if (!r_bin_open (r->bin, filenameuri, &opt)) {
		eprintf ("RBinLoad: Cannot open %s\n", filenameuri);
		if (r_config_get_i (r->config, "bin.rawstr")) {
			r_bin_options_init (&opt, fd, baseaddr, UT64_MAX, true);
			opt.xtr_idx = xtr_idx;
			if (!r_bin_open (r->bin, filenameuri, &opt)) {
				return false;
			}
		}
	}

	if (*r_config_get (r->config, "dbg.libs")) {
		r_core_cmd0 (r, ".dmm*");
#if __linux__
		setbpint (r, "dbg.libs", "sym.imp.dlopen");
		setbpint (r, "dbg.libs", "sym.imp.dlmopen");
		setbpint (r, "dbg.unlibs", "sym.imp.dlclose");
#elif __APPLE__
		setbpint (r, "dbg.libs", "sym._dlopen");
		setbpint (r, "dbg.libs", "sym._dlclose");
#endif
	}
	binfile = r_bin_cur (r->bin);
	r_core_bin_set_env (r, binfile);
	plugin = r_bin_file_cur_plugin (binfile);
	if (plugin && !strncmp (plugin->name, "any", 5)) {
		// set use of raw strings
		// r_config_set_i (r->config, "io.va", false);
		//\\ r_config_set (r->config, "bin.rawstr", "true");
		// get bin.minstr
		r->bin->minstrlen = r_config_get_i (r->config, "bin.minstr");
		r->bin->maxstrbuf = r_config_get_i (r->config, "bin.maxstrbuf");
	} else if (binfile) {
		RBinObject *obj = r_bin_cur_object (r->bin);
		RBinInfo *info = obj? obj->info: NULL;
		if (plugin && strcmp (plugin->name, "any") && info) {
			r_core_bin_set_arch_bits (r, binfile->file, info->arch, info->bits);
		}
	}

	if (plugin && !strcmp (plugin->name, "dex")) {
		r_core_cmd0 (r, "\"(fix-dex,wx `ph sha1 $s-32 @32` @12 ; wx `ph adler32 $s-12 @12` @8)\"\n");
	}

	return true;
}