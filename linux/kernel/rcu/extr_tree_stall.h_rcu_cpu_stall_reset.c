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
struct TYPE_2__ {int /*<<< orphan*/  jiffies_stall; } ;

/* Variables and functions */
 int ULONG_MAX ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ jiffies ; 
 TYPE_1__ rcu_state ; 

void rcu_cpu_stall_reset(void)
{
	WRITE_ONCE(rcu_state.jiffies_stall, jiffies + ULONG_MAX / 2);
}