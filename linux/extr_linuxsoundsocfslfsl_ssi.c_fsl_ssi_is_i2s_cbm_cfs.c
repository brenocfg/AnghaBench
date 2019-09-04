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
struct fsl_ssi {int dai_fmt; } ;

/* Variables and functions */
 int SND_SOC_DAIFMT_CBM_CFS ; 
 int SND_SOC_DAIFMT_MASTER_MASK ; 

__attribute__((used)) static bool fsl_ssi_is_i2s_cbm_cfs(struct fsl_ssi *ssi)
{
	return (ssi->dai_fmt & SND_SOC_DAIFMT_MASTER_MASK) ==
		SND_SOC_DAIFMT_CBM_CFS;
}