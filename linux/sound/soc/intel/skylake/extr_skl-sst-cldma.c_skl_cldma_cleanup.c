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
struct TYPE_4__ {int /*<<< orphan*/  dmab_bdl; int /*<<< orphan*/  dmab_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free_dma_buf ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct sst_dsp {TYPE_2__ cl_dev; int /*<<< orphan*/  dev; TYPE_1__ dsp_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  skl_cldma_cleanup_spb (struct sst_dsp*) ; 
 int /*<<< orphan*/  skl_cldma_stream_clear (struct sst_dsp*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void skl_cldma_cleanup(struct sst_dsp  *ctx)
{
	skl_cldma_cleanup_spb(ctx);
	skl_cldma_stream_clear(ctx);

	ctx->dsp_ops.free_dma_buf(ctx->dev, &ctx->cl_dev.dmab_data);
	ctx->dsp_ops.free_dma_buf(ctx->dev, &ctx->cl_dev.dmab_bdl);
}