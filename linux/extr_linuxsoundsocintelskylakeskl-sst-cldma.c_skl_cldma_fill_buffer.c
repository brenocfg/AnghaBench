#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* cl_trigger ) (struct sst_dsp*,int) ;int /*<<< orphan*/  (* cl_setup_spb ) (struct sst_dsp*,unsigned int,int) ;} ;
struct TYPE_4__ {scalar_t__ area; } ;
struct TYPE_6__ {unsigned int dma_buffer_offset; unsigned int curr_spib_pos; unsigned int bufsize; int wait_condition; TYPE_2__ ops; TYPE_1__ dmab_data; } ;
struct sst_dsp {TYPE_3__ cl_dev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,unsigned int) ; 
 int /*<<< orphan*/  skl_cldma_int_enable (struct sst_dsp*) ; 
 int /*<<< orphan*/  stub1 (struct sst_dsp*,unsigned int,int) ; 
 int /*<<< orphan*/  stub2 (struct sst_dsp*,int) ; 

__attribute__((used)) static void skl_cldma_fill_buffer(struct sst_dsp *ctx, unsigned int size,
		const void *curr_pos, bool intr_enable, bool trigger)
{
	dev_dbg(ctx->dev, "Size: %x, intr_enable: %d\n", size, intr_enable);
	dev_dbg(ctx->dev, "buf_pos_index:%d, trigger:%d\n",
			ctx->cl_dev.dma_buffer_offset, trigger);
	dev_dbg(ctx->dev, "spib position: %d\n", ctx->cl_dev.curr_spib_pos);

	/*
	 * Check if the size exceeds buffer boundary. If it exceeds
	 * max_buffer size, then copy till buffer size and then copy
	 * remaining buffer from the start of ring buffer.
	 */
	if (ctx->cl_dev.dma_buffer_offset + size > ctx->cl_dev.bufsize) {
		unsigned int size_b = ctx->cl_dev.bufsize -
					ctx->cl_dev.dma_buffer_offset;
		memcpy(ctx->cl_dev.dmab_data.area + ctx->cl_dev.dma_buffer_offset,
			curr_pos, size_b);
		size -= size_b;
		curr_pos += size_b;
		ctx->cl_dev.dma_buffer_offset = 0;
	}

	memcpy(ctx->cl_dev.dmab_data.area + ctx->cl_dev.dma_buffer_offset,
			curr_pos, size);

	if (ctx->cl_dev.curr_spib_pos == ctx->cl_dev.bufsize)
		ctx->cl_dev.dma_buffer_offset = 0;
	else
		ctx->cl_dev.dma_buffer_offset = ctx->cl_dev.curr_spib_pos;

	ctx->cl_dev.wait_condition = false;

	if (intr_enable)
		skl_cldma_int_enable(ctx);

	ctx->cl_dev.ops.cl_setup_spb(ctx, ctx->cl_dev.curr_spib_pos, trigger);
	if (trigger)
		ctx->cl_dev.ops.cl_trigger(ctx, true);
}