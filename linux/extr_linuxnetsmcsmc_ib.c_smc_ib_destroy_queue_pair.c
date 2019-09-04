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
struct smc_link {int /*<<< orphan*/ * roce_qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_destroy_qp (int /*<<< orphan*/ *) ; 

void smc_ib_destroy_queue_pair(struct smc_link *lnk)
{
	if (lnk->roce_qp)
		ib_destroy_qp(lnk->roce_qp);
	lnk->roce_qp = NULL;
}