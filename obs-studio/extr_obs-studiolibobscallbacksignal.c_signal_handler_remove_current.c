#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int remove; } ;
struct TYPE_3__ {int remove; } ;

/* Variables and functions */
 TYPE_2__* current_global_cb ; 
 TYPE_1__* current_signal_cb ; 

void signal_handler_remove_current(void)
{
	if (current_signal_cb)
		current_signal_cb->remove = true;
	else if (current_global_cb)
		current_global_cb->remove = true;
}