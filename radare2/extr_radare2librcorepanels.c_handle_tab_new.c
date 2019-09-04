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
struct TYPE_4__ {scalar_t__ n_panels; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 scalar_t__ PANEL_NUM_LIMIT ; 

__attribute__((used)) static bool handle_tab_new(RCore *core) {
	if (core->panels_root->n_panels >= PANEL_NUM_LIMIT) {
		return false;
	}
	core->panels_root->n_panels++;
	return true;
}