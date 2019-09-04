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
struct smcd_dev {int dummy; } ;
struct smc_sock {int dummy; } ;

/* Variables and functions */
 int SMC_CLC_DECL_CNFERR ; 
 scalar_t__ smc_ism_put_vlan (struct smcd_dev*,unsigned short) ; 

__attribute__((used)) static int smc_connect_ism_vlan_cleanup(struct smc_sock *smc, bool is_smcd,
					struct smcd_dev *ismdev,
					unsigned short vlan_id)
{
	if (!is_smcd)
		return 0;
	if (vlan_id && smc_ism_put_vlan(ismdev, vlan_id))
		return SMC_CLC_DECL_CNFERR;
	return 0;
}