#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * panels; } ;
typedef  int /*<<< orphan*/  RPanels ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  checkPanelNum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getCurPanel (int /*<<< orphan*/ *) ; 
 char* r_cons_input (char*) ; 
 int r_cons_yesno (char,char*) ; 
 int /*<<< orphan*/  splitPanelHorizontal (TYPE_1__*,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  splitPanelVertical (TYPE_1__*,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static void createNewPanel(RCore *core, bool vertical) {
	RPanels *panels = core->panels;
	if (!checkPanelNum (panels)) {
		return;
	}
	char *res = r_cons_input ("New panel with command: ");
	if (res && *res) {
		bool cache = r_cons_yesno ('y', "Cache the result? (Y/n)");
		if (res && *res) {
			if (vertical) {
				splitPanelVertical (core, getCurPanel (panels), res, res, cache);
			} else {
				splitPanelHorizontal (core, getCurPanel (panels), res, res, cache);
			}
		}
	}
	free (res);
}