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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int (* cl_copy_to_dmabuf ) (struct sst_dsp*,void const*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* cl_stop_dma ) (struct sst_dsp*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct sst_dsp {TYPE_2__ cl_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKL_ADSP_FW_STATUS ; 
 int /*<<< orphan*/  SKL_BASEFW_TIMEOUT ; 
 int /*<<< orphan*/  SKL_FW_RFW_START ; 
 int /*<<< orphan*/  SKL_FW_STS_MASK ; 
 int sst_dsp_register_poll (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct sst_dsp*,void const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct sst_dsp*) ; 

__attribute__((used)) static int skl_transfer_firmware(struct sst_dsp *ctx,
		const void *basefw, u32 base_fw_size)
{
	int ret = 0;

	ret = ctx->cl_dev.ops.cl_copy_to_dmabuf(ctx, basefw, base_fw_size,
								true);
	if (ret < 0)
		return ret;

	ret = sst_dsp_register_poll(ctx,
			SKL_ADSP_FW_STATUS,
			SKL_FW_STS_MASK,
			SKL_FW_RFW_START,
			SKL_BASEFW_TIMEOUT,
			"Firmware boot");

	ctx->cl_dev.ops.cl_stop_dma(ctx);

	return ret;
}