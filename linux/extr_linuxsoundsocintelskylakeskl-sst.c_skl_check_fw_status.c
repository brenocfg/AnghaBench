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
typedef  int u32 ;
struct sst_dsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKL_ADSP_FW_STATUS ; 
 int SKL_FW_STS_MASK ; 
 int sst_dsp_shim_read (struct sst_dsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool skl_check_fw_status(struct sst_dsp *ctx, u32 status)
{
	u32 cur_sts;

	cur_sts = sst_dsp_shim_read(ctx, SKL_ADSP_FW_STATUS) & SKL_FW_STS_MASK;

	return (cur_sts == status);
}