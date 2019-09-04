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
struct TYPE_3__ {int /*<<< orphan*/ ** panel; } ;
typedef  TYPE_1__ RPanels ;
typedef  int /*<<< orphan*/  RPanel ;

/* Variables and functions */
 int PANEL_NUM_LIMIT ; 

__attribute__((used)) static RPanel *getPanel(RPanels *panels, int i) {
	if (i >= PANEL_NUM_LIMIT) {
		return NULL;
	}
	return panels->panel[i];
}