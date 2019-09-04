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
struct TYPE_2__ {int /*<<< orphan*/  gp_seq; } ;

/* Variables and functions */
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 TYPE_1__ rcu_bh_state ; 

unsigned long rcu_bh_get_gp_seq(void)
{
	return READ_ONCE(rcu_bh_state.gp_seq);
}