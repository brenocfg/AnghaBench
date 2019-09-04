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
struct TYPE_2__ {int /*<<< orphan*/  dynticks_nmi_nesting; int /*<<< orphan*/  dynticks_nesting; } ;

/* Variables and functions */
 int __this_cpu_read (int /*<<< orphan*/ ) ; 
 TYPE_1__ rcu_dynticks ; 

__attribute__((used)) static int rcu_is_cpu_rrupt_from_idle(void)
{
	return __this_cpu_read(rcu_dynticks.dynticks_nesting) <= 0 &&
	       __this_cpu_read(rcu_dynticks.dynticks_nmi_nesting) <= 1;
}