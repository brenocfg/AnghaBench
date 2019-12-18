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
 scalar_t__ r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,int) ; 
 int r_cons_get_size (int*) ; 

__attribute__((used)) static int visual_responsive(RCore *core) {
	int h, w = r_cons_get_size (&h);
	if (r_config_get_i (core->config, "scr.responsive")) {
		if (w < 110) {
			r_config_set_i (core->config, "asm.cmt.right", 0);
		} else {
			r_config_set_i (core->config, "asm.cmt.right", 1);
		}
		if (w < 68) {
			r_config_set_i (core->config, "hex.cols", (int)(w / 5.2));
		} else {
			r_config_set_i (core->config, "hex.cols", 16);
		}
		if (w < 25) {
			r_config_set_i (core->config, "asm.offset", 0);
		} else {
			r_config_set_i (core->config, "asm.offset", 1);
		}
		if (w > 80) {
			r_config_set_i (core->config, "asm.lines.width", 14);
			r_config_set_i (core->config, "asm.lines.width", w - (int)(w / 1.2));
			r_config_set_i (core->config, "asm.cmt.col", w - (int)(w / 2.5));
		} else {
			r_config_set_i (core->config, "asm.lines.width", 7);
		}
		if (w < 70) {
			r_config_set_i (core->config, "asm.lines.width", 1);
			r_config_set_i (core->config, "asm.bytes", 0);
		} else {
			r_config_set_i (core->config, "asm.bytes", 1);
		}
	}
	return w;
}