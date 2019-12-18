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
struct smc_link_group {int /*<<< orphan*/ * lnk; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  smcd; scalar_t__ is_smcd; } ;

/* Variables and functions */
 size_t SMC_SINGLE_LINK ; 
 int /*<<< orphan*/  kfree (struct smc_link_group*) ; 
 int /*<<< orphan*/  smc_ism_put_vlan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_lgr_free_bufs (struct smc_link_group*) ; 
 int /*<<< orphan*/  smc_link_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smc_lgr_free(struct smc_link_group *lgr)
{
	smc_lgr_free_bufs(lgr);
	if (lgr->is_smcd)
		smc_ism_put_vlan(lgr->smcd, lgr->vlan_id);
	else
		smc_link_clear(&lgr->lnk[SMC_SINGLE_LINK]);
	kfree(lgr);
}