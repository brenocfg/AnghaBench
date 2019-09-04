#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int n_panels; int /*<<< orphan*/  panel; } ;
typedef  TYPE_1__ RPanels ;
typedef  int /*<<< orphan*/  RPanel ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeSinglePanel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getPanel (TYPE_1__*,int) ; 

__attribute__((used)) static void freeAllPanels(RPanels *panels) {
	int i;
	for (i = 0; i < panels->n_panels; i++) {
		RPanel *p = getPanel (panels, i);
		freeSinglePanel (p);
	}
	free (panels->panel);
}