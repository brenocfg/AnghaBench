#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ name; scalar_t__ info; } ;
struct TYPE_6__ {int /*<<< orphan*/  bin; int /*<<< orphan*/  config; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_1__ RCore ;
typedef  TYPE_2__ RBinPlugin ;
typedef  int /*<<< orphan*/  RBinFile ;

/* Variables and functions */
 scalar_t__ IS_MODE_JSON (int) ; 
 int /*<<< orphan*/  _print_strings (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * r_bin_cur (int /*<<< orphan*/ ) ; 
 TYPE_2__* r_bin_file_cur_plugin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_bin_get_strings (int /*<<< orphan*/ ) ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_cons_print (char*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

__attribute__((used)) static bool bin_strings(RCore *r, int mode, int va) {
	RList *list;
	RBinFile *binfile = r_bin_cur (r->bin);
	RBinPlugin *plugin = r_bin_file_cur_plugin (binfile);
	int rawstr = r_config_get_i (r->config, "bin.rawstr");
	if (!binfile) {
		return false;
	}
	if (!r_config_get_i (r->config, "bin.strings")) {
		return false;
	}
	if (!plugin) {
		return false;
	}
	if (plugin->info && plugin->name) {
		if (strcmp (plugin->name, "any") == 0 && !rawstr) {
			if (IS_MODE_JSON (mode)) {
				r_cons_print("[]");
			}
			return false;
		}
	}

	if (!(list = r_bin_get_strings (r->bin))) {
		return false;
	}
	_print_strings (r, list, mode, va);
	return true;
}