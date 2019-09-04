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
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int PF_KTHREAD ; 
 TYPE_1__* current ; 
 scalar_t__ kthread_should_stop () ; 

__attribute__((used)) static inline bool is_kthread_should_stop(void)
{
	return (current->flags & PF_KTHREAD) && kthread_should_stop();
}