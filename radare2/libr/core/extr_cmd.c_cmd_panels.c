#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  panels_root; int /*<<< orphan*/  config; scalar_t__ panels; scalar_t__ vmode; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char const*) ; 
 char* r_core_editor (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_core_visual_panels_root (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_load_panels_layout (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  r_save_panels_layout (TYPE_1__*,char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int cmd_panels(void *data, const char *input) {
	RCore *core = (RCore*) data;
	if (core->vmode) {
		return false;
	}
	if (*input == '?') {
		eprintf ("Usage: v[*i]\n");
		eprintf ("v.test    # save current layout with name test\n");
		eprintf ("v test    # load saved layout with name test\n");
		eprintf ("vi ...    # launch 'cfg.editor'\n");
		return false;
	}
	if (*input == ' ') {
		if (core->panels) {
			r_load_panels_layout (core, input + 1);
		}
		r_config_set (core->config, "scr.layout", input + 1);
		return true;
	}
	if (*input == '=') {
		r_save_panels_layout (core, input + 1);
		r_config_set (core->config, "scr.layout", input + 1);
		return true;
	}
	if (*input == 'i') {
		char *sp = strchr (input, ' ');
		if (sp) {
			char *r = r_core_editor (core, sp + 1, NULL);
			if (r) {
				free (r);
			} else {
				eprintf ("Cannot open file (%s)\n", sp + 1);
			}
		}
		////r_sys_cmdf ("v%s", input);
		return false;
	}
	r_core_visual_panels_root (core, core->panels_root);
	return true;
}