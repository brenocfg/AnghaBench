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
struct smc_link_group {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __smc_lgr_terminate (struct smc_link_group*) ; 
 TYPE_1__ smc_lgr_list ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void smc_lgr_terminate(struct smc_link_group *lgr)
{
	spin_lock_bh(&smc_lgr_list.lock);
	__smc_lgr_terminate(lgr);
	spin_unlock_bh(&smc_lgr_list.lock);
}