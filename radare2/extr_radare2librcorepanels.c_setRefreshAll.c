#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* view; } ;
struct TYPE_9__ {int n_panels; } ;
struct TYPE_8__ {int refresh; } ;
typedef  TYPE_2__ RPanels ;
typedef  TYPE_3__ RPanel ;

/* Variables and functions */
 TYPE_3__* getPanel (TYPE_2__*,int) ; 
 int /*<<< orphan*/  setCmdStrCache (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setRefreshAll(RPanels *panels, bool clearCache) {
	int i;
	for (i = 0; i < panels->n_panels; i++) {
		RPanel *panel = getPanel (panels, i);
		panel->view->refresh = true;
		if (clearCache) {
			setCmdStrCache (panel, NULL);
		}
	}
}