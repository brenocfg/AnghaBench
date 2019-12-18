#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RPanel ;

/* Variables and functions */
 int /*<<< orphan*/  __free_panel_model (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __free_panel_view (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void __free_single_panel(RPanel *panel) {
	__free_panel_model (panel);
	__free_panel_view (panel);
	free (panel);
}