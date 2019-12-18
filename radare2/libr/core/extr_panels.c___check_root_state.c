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
struct TYPE_4__ {scalar_t__ root_state; } ;
typedef  scalar_t__ RPanelsRootState ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */

bool __check_root_state(RCore *core, RPanelsRootState state) {
	return core->panels_root->root_state == state;
}