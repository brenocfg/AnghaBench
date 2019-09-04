#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* panels_root; } ;
struct TYPE_4__ {int cur_panels; int n_panels; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 scalar_t__ isdigit (int) ; 

__attribute__((used)) static bool handle_tab_nth(RCore *core, int ch) {
	if (isdigit (ch)) {
		ch -= '0' + 1;
		if (ch != core->panels_root->cur_panels && ch < core->panels_root->n_panels) {
			core->panels_root->cur_panels = ch;
			return true;
		}
	}
	return false;
}