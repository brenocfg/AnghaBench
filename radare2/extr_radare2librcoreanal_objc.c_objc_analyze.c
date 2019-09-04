#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  print; int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_config_get (int /*<<< orphan*/ ,char*) ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  r_core_cmd0 (TYPE_1__*,char*) ; 
 char* r_print_rowlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_print_rowlog_done (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void objc_analyze(RCore *core) {
	static const char *oldstr = NULL;
	oldstr = r_print_rowlog (core->print, "Analyzing searching references to selref");
	r_core_cmd0 (core, "aar");
	if (!strcmp ("arm", r_config_get (core->config, "asm.arch"))) {
		bool emu_lazy = r_config_get_i (core->config, "emu.lazy");
		r_config_set_i (core->config, "emu.lazy", true);
		r_core_cmd0 (core, "aae");
		r_config_set_i (core->config, "emu.lazy", emu_lazy);
	}
	r_print_rowlog_done (core->print, oldstr);
}