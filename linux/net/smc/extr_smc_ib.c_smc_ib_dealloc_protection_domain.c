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
struct smc_link {int /*<<< orphan*/ * roce_pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dealloc_pd (int /*<<< orphan*/ *) ; 

void smc_ib_dealloc_protection_domain(struct smc_link *lnk)
{
	if (lnk->roce_pd)
		ib_dealloc_pd(lnk->roce_pd);
	lnk->roce_pd = NULL;
}