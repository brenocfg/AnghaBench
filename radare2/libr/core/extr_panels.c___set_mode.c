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
struct TYPE_7__ {TYPE_1__* panels; } ;
struct TYPE_6__ {int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  RPanelsMode ;
typedef  TYPE_1__ RPanels ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __set_cursor (TYPE_2__*,int) ; 
 int /*<<< orphan*/  __update_help (TYPE_1__*) ; 

void __set_mode(RCore *core, RPanelsMode mode) {
	RPanels *panels = core->panels;
	__set_cursor (core, false);
	panels->mode = mode;
	__update_help (panels);
}