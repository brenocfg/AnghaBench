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
struct TYPE_3__ {int n_sub; scalar_t__ selectedIndex; struct TYPE_3__** sub; } ;
typedef  TYPE_1__ RPanelsMenuItem ;

/* Variables and functions */

void __clear_panels_menuRec(RPanelsMenuItem *pmi) {
	int i = 0;
	for(i = 0; i < pmi->n_sub; i++) {
		RPanelsMenuItem *sub = pmi->sub[i];
		if (sub) {
			sub->selectedIndex = 0;
			__clear_panels_menuRec (sub);
		}
	}
}