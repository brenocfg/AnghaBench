#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* panels; } ;
struct TYPE_7__ {scalar_t__ curnode; } ;
typedef  TYPE_1__ RPanels ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  insertPanel (TYPE_2__*,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  panels_layout (TYPE_1__*) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_1__*,int) ; 

__attribute__((used)) static void addNewPanel(RCore *core, char *name, char *cmd, bool cache) {
	RPanels *panels = core->panels;
	insertPanel (core, 0, name, cmd, cache);
	panels_layout (panels);
	panels->curnode = 0;
	setRefreshAll (panels, false);
}