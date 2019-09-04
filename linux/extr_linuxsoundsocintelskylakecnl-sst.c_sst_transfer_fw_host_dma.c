#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  stream_tag; int /*<<< orphan*/  (* cleanup ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* trigger ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct sst_dsp {TYPE_1__ dsp_ops; int /*<<< orphan*/  dmab; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_ADSP_FW_STATUS ; 
 int /*<<< orphan*/  CNL_BASEFW_TIMEOUT ; 
 int /*<<< orphan*/  CNL_FW_INIT ; 
 int /*<<< orphan*/  CNL_FW_STS_MASK ; 
 int sst_dsp_register_poll (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sst_transfer_fw_host_dma(struct sst_dsp *ctx)
{
	int ret;

	ctx->dsp_ops.trigger(ctx->dev, true, ctx->dsp_ops.stream_tag);
	ret = sst_dsp_register_poll(ctx, CNL_ADSP_FW_STATUS, CNL_FW_STS_MASK,
				    CNL_FW_INIT, CNL_BASEFW_TIMEOUT,
				    "firmware boot");

	ctx->dsp_ops.trigger(ctx->dev, false, ctx->dsp_ops.stream_tag);
	ctx->dsp_ops.cleanup(ctx->dev, &ctx->dmab, ctx->dsp_ops.stream_tag);

	return ret;
}