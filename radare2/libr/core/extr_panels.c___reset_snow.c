#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* view; } ;
struct TYPE_8__ {int /*<<< orphan*/ * snows; } ;
struct TYPE_7__ {int refresh; } ;
typedef  TYPE_2__ RPanels ;
typedef  TYPE_3__ RPanel ;

/* Variables and functions */
 TYPE_3__* __get_cur_panel (TYPE_2__*) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 

void __reset_snow(RPanels *panels) {
	RPanel *cur = __get_cur_panel (panels);
	r_list_free (panels->snows);
	panels->snows = NULL;
	cur->view->refresh = true;
}