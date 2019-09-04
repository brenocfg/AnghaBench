#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_31__ {int /*<<< orphan*/  file; } ;
struct TYPE_30__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  arch; } ;
struct TYPE_29__ {TYPE_6__* info; } ;
struct TYPE_28__ {int xtr_idx; } ;
struct TYPE_27__ {int /*<<< orphan*/  name; } ;
struct TYPE_26__ {TYPE_16__* bin; int /*<<< orphan*/  config; int /*<<< orphan*/  io; } ;
struct TYPE_25__ {int fd; } ;
struct TYPE_24__ {void* maxstrbuf; void* minstrlen; int /*<<< orphan*/  rawstr; } ;
typedef  TYPE_1__ RCoreFile ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RBinPlugin ;
typedef  TYPE_4__ RBinOptions ;
typedef  TYPE_5__ RBinObject ;
typedef  TYPE_6__ RBinInfo ;
typedef  TYPE_7__ RBinFile ;

/* Variables and functions */
 TYPE_7__* r_bin_cur (TYPE_16__*) ; 
 TYPE_5__* r_bin_cur_object (TYPE_16__*) ; 
 TYPE_3__* r_bin_file_cur_plugin (TYPE_7__*) ; 
 int /*<<< orphan*/  r_bin_open_io (TYPE_16__*,TYPE_4__*) ; 
 int /*<<< orphan*/  r_bin_options_init (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_core_bin_set_arch_bits (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_bin_set_env (TYPE_2__*,TYPE_7__*) ; 
 int /*<<< orphan*/  r_core_cmd0 (TYPE_2__*,char*) ; 
 TYPE_1__* r_core_file_cur (TYPE_2__*) ; 
 int /*<<< orphan*/  r_io_use_fd (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int r_core_file_do_load_for_io_plugin(RCore *r, ut64 baseaddr, ut64 loadaddr) {
	RCoreFile *cf = r_core_file_cur (r);
	int fd = cf ? cf->fd : -1;
	RBinFile *binfile = NULL;
	int xtr_idx = 0; // if 0, load all if xtr is used
	RBinPlugin *plugin;

	if (fd < 0) {
		return false;
	}
	r_io_use_fd (r->io, fd);
	RBinOptions opt;
	r_bin_options_init (&opt, fd, baseaddr, loadaddr, r->bin->rawstr);
	opt.xtr_idx = xtr_idx;
	if (!r_bin_open_io (r->bin, &opt)) {
		//eprintf ("Failed to load the bin with an IO Plugin.\n");
		return false;
	}
	binfile = r_bin_cur (r->bin);
	r_core_bin_set_env (r, binfile);
	plugin = r_bin_file_cur_plugin (binfile);
	if (plugin && !strcmp (plugin->name, "any")) {
		RBinObject *obj = r_bin_cur_object (r->bin);
		RBinInfo *info = obj? obj->info: NULL;
		if (!info) {
			return false;
		}
		// set use of raw strings
		r_core_bin_set_arch_bits (r, binfile->file, info->arch, info->bits);
		// r_config_set_i (r->config, "io.va", false);
		// r_config_set (r->config, "bin.rawstr", "true");
		// get bin.minstr
		r->bin->minstrlen = r_config_get_i (r->config, "bin.minstr");
		r->bin->maxstrbuf = r_config_get_i (r->config, "bin.maxstrbuf");
	} else if (binfile) {
		RBinObject *obj = r_bin_cur_object (r->bin);
		RBinInfo *info = obj? obj->info: NULL;
		if (!info) {
			return false;
		}
		if (plugin && strcmp (plugin->name, "any") && info) {
			r_core_bin_set_arch_bits (r, binfile->file,
				info->arch, info->bits);
		}
	}

	if (plugin && !strcmp (plugin->name, "dex")) {
		r_core_cmd0 (r, "\"(fix-dex,wx `ph sha1 $s-32 @32` @12 ; wx `ph adler32 $s-12 @12` @8)\"\n");
	}
	return true;
}