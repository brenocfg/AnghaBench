#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smt_p_mac_counter {int /*<<< orphan*/  mc_transmit_ct; int /*<<< orphan*/  mc_receive_ct; int /*<<< orphan*/  mc_index; int /*<<< orphan*/  mc_mib_index; } ;
struct TYPE_3__ {TYPE_2__* m; } ;
struct s_smc {TYPE_1__ mib; } ;
struct TYPE_4__ {int /*<<< orphan*/  fddiMACTransmit_Ct; int /*<<< orphan*/  fddiMACCopied_Ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  INDEX_MAC ; 
 size_t MAC0 ; 
 int /*<<< orphan*/  SMTSETPARA (struct smt_p_mac_counter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMT_P_MAC_COUNTER ; 
 int /*<<< orphan*/  mac_index (struct s_smc*,int) ; 

__attribute__((used)) static void smt_fill_mac_counter(struct s_smc *smc, struct smt_p_mac_counter *mc)
{
	SMTSETPARA(mc,SMT_P_MAC_COUNTER) ;
	mc->mc_mib_index = INDEX_MAC ;
	mc->mc_index = mac_index(smc,1) ;
	mc->mc_receive_ct = smc->mib.m[MAC0].fddiMACCopied_Ct ;
	mc->mc_transmit_ct =  smc->mib.m[MAC0].fddiMACTransmit_Ct ;
}