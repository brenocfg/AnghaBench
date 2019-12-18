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
struct TYPE_4__ {int /*<<< orphan*/  (* cl_cleanup_controller ) (struct sst_dsp*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;
struct sst_dsp {TYPE_2__ cl_dev; int /*<<< orphan*/  dev; struct skl_dev* thread_context; } ;
struct skl_ipc_dxstate_info {unsigned int core_mask; int /*<<< orphan*/  dx_mask; } ;
struct TYPE_6__ {int /*<<< orphan*/ * state; } ;
struct skl_dev {TYPE_3__ cores; int /*<<< orphan*/  ipc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKL_BASE_FW_MODULE_ID ; 
 unsigned int SKL_DSP_CORE0_ID ; 
 unsigned int SKL_DSP_CORE_MASK (unsigned int) ; 
 int /*<<< orphan*/  SKL_DSP_RESET ; 
 int /*<<< orphan*/  SKL_INSTANCE_ID ; 
 int /*<<< orphan*/  SKL_IPC_D3_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  skl_cldma_int_disable (struct sst_dsp*) ; 
 int skl_dsp_disable_core (struct sst_dsp*,unsigned int) ; 
 int /*<<< orphan*/  skl_ipc_int_disable (struct sst_dsp*) ; 
 int /*<<< orphan*/  skl_ipc_op_int_disable (struct sst_dsp*) ; 
 int skl_ipc_set_dx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct skl_ipc_dxstate_info*) ; 
 int /*<<< orphan*/  stub1 (struct sst_dsp*) ; 

__attribute__((used)) static int skl_set_dsp_D3(struct sst_dsp *ctx, unsigned int core_id)
{
	int ret;
	struct skl_ipc_dxstate_info dx;
	struct skl_dev *skl = ctx->thread_context;
	unsigned int core_mask = SKL_DSP_CORE_MASK(core_id);

	dx.core_mask = core_mask;
	dx.dx_mask = SKL_IPC_D3_MASK;

	ret = skl_ipc_set_dx(&skl->ipc, SKL_INSTANCE_ID, SKL_BASE_FW_MODULE_ID, &dx);
	if (ret < 0)
		dev_err(ctx->dev, "set Dx core %d fail: %d\n", core_id, ret);

	if (core_id == SKL_DSP_CORE0_ID) {
		/* disable Interrupt */
		ctx->cl_dev.ops.cl_cleanup_controller(ctx);
		skl_cldma_int_disable(ctx);
		skl_ipc_op_int_disable(ctx);
		skl_ipc_int_disable(ctx);
	}

	ret = skl_dsp_disable_core(ctx, core_mask);
	if (ret < 0)
		return ret;

	skl->cores.state[core_id] = SKL_DSP_RESET;
	return ret;
}