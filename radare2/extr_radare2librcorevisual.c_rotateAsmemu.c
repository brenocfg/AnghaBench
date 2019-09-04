#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static const char *rotateAsmemu(RCore *core) {
	const bool isEmuStr = r_config_get_i (core->config, "emu.str");
	const bool isEmu = r_config_get_i (core->config, "asm.emu");
	if (isEmu) {
		if (isEmuStr) {
			r_config_set (core->config, "emu.str", "false");
		} else {
			r_config_set (core->config, "asm.emu", "false");
		}
	} else {
		r_config_set (core->config, "emu.str", "true");
	}
	return "pd";
}