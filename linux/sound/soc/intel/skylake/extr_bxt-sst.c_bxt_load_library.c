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
struct TYPE_2__ {int (* prepare ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct snd_dma_buffer*) ;int /*<<< orphan*/  (* cleanup ) (int /*<<< orphan*/ ,struct snd_dma_buffer*,int) ;int /*<<< orphan*/  (* trigger ) (int /*<<< orphan*/ ,int,int) ;} ;
struct sst_dsp {int /*<<< orphan*/  dev; TYPE_1__ dsp_ops; struct skl_dev* thread_context; } ;
struct snd_dma_buffer {int /*<<< orphan*/  area; } ;
struct skl_lib_info {int /*<<< orphan*/  name; } ;
struct skl_dev {int /*<<< orphan*/  ipc; int /*<<< orphan*/ * lib_info; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_ADSP_FW_BIN_HDR_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skl_prepare_lib_load (struct skl_dev*,int /*<<< orphan*/ *,struct firmware*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skl_release_library (struct skl_lib_info*,int) ; 
 int skl_sst_ipc_load_library (int /*<<< orphan*/ *,int,int,int) ; 
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct snd_dma_buffer*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,struct snd_dma_buffer*,int) ; 

__attribute__((used)) static int
bxt_load_library(struct sst_dsp *ctx, struct skl_lib_info *linfo, int lib_count)
{
	struct snd_dma_buffer dmab;
	struct skl_dev *skl = ctx->thread_context;
	struct firmware stripped_fw;
	int ret = 0, i, dma_id, stream_tag;

	/* library indices start from 1 to N. 0 represents base FW */
	for (i = 1; i < lib_count; i++) {
		ret = skl_prepare_lib_load(skl, &skl->lib_info[i], &stripped_fw,
					BXT_ADSP_FW_BIN_HDR_OFFSET, i);
		if (ret < 0)
			goto load_library_failed;

		stream_tag = ctx->dsp_ops.prepare(ctx->dev, 0x40,
					stripped_fw.size, &dmab);
		if (stream_tag <= 0) {
			dev_err(ctx->dev, "Lib prepare DMA err: %x\n",
					stream_tag);
			ret = stream_tag;
			goto load_library_failed;
		}

		dma_id = stream_tag - 1;
		memcpy(dmab.area, stripped_fw.data, stripped_fw.size);

		ctx->dsp_ops.trigger(ctx->dev, true, stream_tag);
		ret = skl_sst_ipc_load_library(&skl->ipc, dma_id, i, true);
		if (ret < 0)
			dev_err(ctx->dev, "IPC Load Lib for %s fail: %d\n",
					linfo[i].name, ret);

		ctx->dsp_ops.trigger(ctx->dev, false, stream_tag);
		ctx->dsp_ops.cleanup(ctx->dev, &dmab, stream_tag);
	}

	return ret;

load_library_failed:
	skl_release_library(linfo, lib_count);
	return ret;
}