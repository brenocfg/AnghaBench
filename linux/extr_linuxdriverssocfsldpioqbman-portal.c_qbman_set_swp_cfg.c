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
typedef  int u32 ;

/* Variables and functions */
 int SWP_CFG_DCM_SHIFT ; 
 int SWP_CFG_DE_SHIFT ; 
 int SWP_CFG_DP_SHIFT ; 
 int SWP_CFG_DQRR_MF_SHIFT ; 
 int SWP_CFG_EPM_SHIFT ; 
 int SWP_CFG_EP_SHIFT ; 
 int SWP_CFG_EST_SHIFT ; 
 int SWP_CFG_RPM_SHIFT ; 
 int SWP_CFG_SD_SHIFT ; 
 int SWP_CFG_SE_SHIFT ; 
 int SWP_CFG_SP_SHIFT ; 
 int SWP_CFG_WN_SHIFT ; 

__attribute__((used)) static inline u32 qbman_set_swp_cfg(u8 max_fill, u8 wn,	u8 est, u8 rpm, u8 dcm,
				    u8 epm, int sd, int sp, int se,
				    int dp, int de, int ep)
{
	return (max_fill << SWP_CFG_DQRR_MF_SHIFT |
		est << SWP_CFG_EST_SHIFT |
		wn << SWP_CFG_WN_SHIFT |
		rpm << SWP_CFG_RPM_SHIFT |
		dcm << SWP_CFG_DCM_SHIFT |
		epm << SWP_CFG_EPM_SHIFT |
		sd << SWP_CFG_SD_SHIFT |
		sp << SWP_CFG_SP_SHIFT |
		se << SWP_CFG_SE_SHIFT |
		dp << SWP_CFG_DP_SHIFT |
		de << SWP_CFG_DE_SHIFT |
		ep << SWP_CFG_EP_SHIFT);
}