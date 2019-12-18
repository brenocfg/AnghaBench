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
struct TYPE_3__ {int /*<<< orphan*/  config; scalar_t__ vmode; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_cons_enable_mouse (int) ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 int /*<<< orphan*/  r_cons_show_cursor (int) ; 

__attribute__((used)) static void showcursor(RCore *core, int x) {
	if (core && core->vmode) {
		r_cons_show_cursor (x);
		r_cons_enable_mouse (x? r_config_get_i (core->config, "scr.wheel"): false);
	} else {
		r_cons_enable_mouse (false);
	}
	r_cons_flush ();
}