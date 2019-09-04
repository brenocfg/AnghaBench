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
struct rcu_sync {int /*<<< orphan*/  gp_state; int /*<<< orphan*/  gp_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GP_PASSED ; 

void rcu_sync_enter_start(struct rcu_sync *rsp)
{
	rsp->gp_count++;
	rsp->gp_state = GP_PASSED;
}