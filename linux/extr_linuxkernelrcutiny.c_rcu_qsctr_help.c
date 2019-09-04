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
struct rcu_ctrlblk {scalar_t__ donetail; scalar_t__ curtail; } ;

/* Variables and functions */

__attribute__((used)) static int rcu_qsctr_help(struct rcu_ctrlblk *rcp)
{
	if (rcp->donetail != rcp->curtail) {
		rcp->donetail = rcp->curtail;
		return 1;
	}

	return 0;
}