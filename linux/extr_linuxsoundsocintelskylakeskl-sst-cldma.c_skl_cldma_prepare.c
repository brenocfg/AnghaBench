#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ area; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* cl_setup_controller ) (struct sst_dsp*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cl_setup_bdle ) (struct sst_dsp*,TYPE_4__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  cl_stop_dma; int /*<<< orphan*/  cl_copy_to_dmabuf; int /*<<< orphan*/  cl_cleanup_controller; int /*<<< orphan*/  cl_trigger; int /*<<< orphan*/  cl_cleanup_spb; int /*<<< orphan*/  cl_setup_spb; } ;
struct TYPE_13__ {int /*<<< orphan*/  wait_queue; scalar_t__ dma_buffer_offset; scalar_t__ curr_spib_pos; int /*<<< orphan*/  frags; int /*<<< orphan*/  bufsize; TYPE_4__ dmab_bdl; TYPE_2__ ops; TYPE_4__ dmab_data; } ;
struct TYPE_11__ {int (* alloc_dma_buf ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* free_dma_buf ) (int /*<<< orphan*/ ,TYPE_4__*) ;} ;
struct sst_dsp {TYPE_3__ cl_dev; int /*<<< orphan*/  dev; TYPE_1__ dsp_ops; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SKL_MAX_BUFFER_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skl_cldma_cleanup ; 
 int /*<<< orphan*/  skl_cldma_cleanup_spb ; 
 int /*<<< orphan*/  skl_cldma_copy_to_buf ; 
 int /*<<< orphan*/  skl_cldma_setup_bdle (struct sst_dsp*,TYPE_4__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skl_cldma_setup_controller (struct sst_dsp*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_cldma_setup_spb ; 
 int /*<<< orphan*/  skl_cldma_stop ; 
 int /*<<< orphan*/  skl_cldma_stream_run ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  stub4 (struct sst_dsp*,TYPE_4__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct sst_dsp*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int skl_cldma_prepare(struct sst_dsp *ctx)
{
	int ret;
	__le32 *bdl;

	ctx->cl_dev.bufsize = SKL_MAX_BUFFER_SIZE;

	/* Allocate cl ops */
	ctx->cl_dev.ops.cl_setup_bdle = skl_cldma_setup_bdle;
	ctx->cl_dev.ops.cl_setup_controller = skl_cldma_setup_controller;
	ctx->cl_dev.ops.cl_setup_spb = skl_cldma_setup_spb;
	ctx->cl_dev.ops.cl_cleanup_spb = skl_cldma_cleanup_spb;
	ctx->cl_dev.ops.cl_trigger = skl_cldma_stream_run;
	ctx->cl_dev.ops.cl_cleanup_controller = skl_cldma_cleanup;
	ctx->cl_dev.ops.cl_copy_to_dmabuf = skl_cldma_copy_to_buf;
	ctx->cl_dev.ops.cl_stop_dma = skl_cldma_stop;

	/* Allocate buffer*/
	ret = ctx->dsp_ops.alloc_dma_buf(ctx->dev,
			&ctx->cl_dev.dmab_data, ctx->cl_dev.bufsize);
	if (ret < 0) {
		dev_err(ctx->dev, "Alloc buffer for base fw failed: %x\n", ret);
		return ret;
	}
	/* Setup Code loader BDL */
	ret = ctx->dsp_ops.alloc_dma_buf(ctx->dev,
			&ctx->cl_dev.dmab_bdl, PAGE_SIZE);
	if (ret < 0) {
		dev_err(ctx->dev, "Alloc buffer for blde failed: %x\n", ret);
		ctx->dsp_ops.free_dma_buf(ctx->dev, &ctx->cl_dev.dmab_data);
		return ret;
	}
	bdl = (__le32 *)ctx->cl_dev.dmab_bdl.area;

	/* Allocate BDLs */
	ctx->cl_dev.ops.cl_setup_bdle(ctx, &ctx->cl_dev.dmab_data,
			&bdl, ctx->cl_dev.bufsize, 1);
	ctx->cl_dev.ops.cl_setup_controller(ctx, &ctx->cl_dev.dmab_bdl,
			ctx->cl_dev.bufsize, ctx->cl_dev.frags);

	ctx->cl_dev.curr_spib_pos = 0;
	ctx->cl_dev.dma_buffer_offset = 0;
	init_waitqueue_head(&ctx->cl_dev.wait_queue);

	return ret;
}