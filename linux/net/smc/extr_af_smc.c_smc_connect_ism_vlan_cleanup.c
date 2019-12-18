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
struct smc_sock {int dummy; } ;
struct smc_init_info {scalar_t__ vlan_id; int /*<<< orphan*/  ism_dev; } ;

/* Variables and functions */
 int SMC_CLC_DECL_CNFERR ; 
 scalar_t__ smc_ism_put_vlan (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int smc_connect_ism_vlan_cleanup(struct smc_sock *smc, bool is_smcd,
					struct smc_init_info *ini)
{
	if (!is_smcd)
		return 0;
	if (ini->vlan_id && smc_ism_put_vlan(ini->ism_dev, ini->vlan_id))
		return SMC_CLC_DECL_CNFERR;
	return 0;
}