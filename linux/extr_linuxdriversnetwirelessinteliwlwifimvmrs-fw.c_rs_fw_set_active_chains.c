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
typedef  int u8 ;

/* Variables and functions */
 int ANT_A ; 
 int ANT_B ; 
 int ANT_C ; 
 int IWL_TLC_MNG_CHAIN_A_MSK ; 
 int IWL_TLC_MNG_CHAIN_B_MSK ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 

__attribute__((used)) static u8 rs_fw_set_active_chains(u8 chains)
{
	u8 fw_chains = 0;

	if (chains & ANT_A)
		fw_chains |= IWL_TLC_MNG_CHAIN_A_MSK;
	if (chains & ANT_B)
		fw_chains |= IWL_TLC_MNG_CHAIN_B_MSK;
	if (chains & ANT_C)
		WARN(false,
		     "tlc offload doesn't support antenna C. chains: 0x%x\n",
		     chains);

	return fw_chains;
}