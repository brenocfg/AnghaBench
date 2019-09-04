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
typedef  enum cpuhp_state { ____Placeholder_cpuhp_state } cpuhp_state ;
struct TYPE_3__ {void* single; } ;
struct TYPE_4__ {TYPE_1__ teardown; } ;

/* Variables and functions */
 TYPE_2__* cpuhp_get_step (int) ; 

__attribute__((used)) static void *cpuhp_get_teardown_cb(enum cpuhp_state state)
{
	return cpuhp_get_step(state)->teardown.single;
}