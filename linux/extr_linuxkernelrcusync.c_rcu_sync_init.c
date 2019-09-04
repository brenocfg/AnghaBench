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
struct rcu_sync {int gp_type; int /*<<< orphan*/  gp_wait; } ;
typedef  enum rcu_sync_type { ____Placeholder_rcu_sync_type } rcu_sync_type ;

/* Variables and functions */
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct rcu_sync*,int /*<<< orphan*/ ,int) ; 

void rcu_sync_init(struct rcu_sync *rsp, enum rcu_sync_type type)
{
	memset(rsp, 0, sizeof(*rsp));
	init_waitqueue_head(&rsp->gp_wait);
	rsp->gp_type = type;
}