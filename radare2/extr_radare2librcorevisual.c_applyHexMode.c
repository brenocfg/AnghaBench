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
 int R_ABS (int) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void applyHexMode(RCore *core, int hexMode) {
	switch (R_ABS(hexMode) % 3) {
	case 0:
		r_config_set (core->config, "hex.compact", "false");
		r_config_set (core->config, "hex.comments", "true");
		break;
	case 1:
		r_config_set (core->config, "hex.compact", "true");
		r_config_set (core->config, "hex.comments", "true");
		break;
	case 2:
		r_config_set (core->config, "hex.compact", "false");
		r_config_set (core->config, "hex.comments", "false");
		break;
	}
}