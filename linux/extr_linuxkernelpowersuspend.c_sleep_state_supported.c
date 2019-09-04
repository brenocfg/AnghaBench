#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ suspend_state_t ;
struct TYPE_2__ {scalar_t__ enter; } ;

/* Variables and functions */
 scalar_t__ PM_SUSPEND_TO_IDLE ; 
 TYPE_1__* suspend_ops ; 

__attribute__((used)) static bool sleep_state_supported(suspend_state_t state)
{
	return state == PM_SUSPEND_TO_IDLE || (suspend_ops && suspend_ops->enter);
}