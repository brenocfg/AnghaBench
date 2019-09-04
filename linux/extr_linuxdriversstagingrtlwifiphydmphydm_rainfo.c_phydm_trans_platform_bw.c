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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 scalar_t__ HT_CHANNEL_WIDTH_20_40 ; 
 scalar_t__ HT_CHANNEL_WIDTH_80 ; 
 scalar_t__ PHYDM_BW_20 ; 
 scalar_t__ PHYDM_BW_40 ; 
 scalar_t__ PHYDM_BW_80 ; 

__attribute__((used)) static u8 phydm_trans_platform_bw(void *dm_void, u8 BW)
{
	if (BW == HT_CHANNEL_WIDTH_20)
		BW = PHYDM_BW_20;

	else if (BW == HT_CHANNEL_WIDTH_20_40)
		BW = PHYDM_BW_40;

	else if (BW == HT_CHANNEL_WIDTH_80)
		BW = PHYDM_BW_80;

	return BW;
}