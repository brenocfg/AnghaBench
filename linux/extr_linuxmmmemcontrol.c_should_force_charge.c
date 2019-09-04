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
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int PF_EXITING ; 
 TYPE_1__* current ; 
 scalar_t__ fatal_signal_pending (TYPE_1__*) ; 
 scalar_t__ tsk_is_oom_victim (TYPE_1__*) ; 

__attribute__((used)) static inline bool should_force_charge(void)
{
	return tsk_is_oom_victim(current) || fatal_signal_pending(current) ||
		(current->flags & PF_EXITING);
}