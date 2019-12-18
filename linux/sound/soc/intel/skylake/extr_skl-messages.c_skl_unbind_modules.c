#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct skl_module_inst_id {int /*<<< orphan*/  pvt_id; int /*<<< orphan*/  module_id; } ;
struct skl_module_cfg {TYPE_2__* m_out_pin; TYPE_2__* m_in_pin; struct skl_module_inst_id id; TYPE_1__* module; } ;
struct skl_ipc_bind_unbind_msg {int src_queue; int dst_queue; int bind; int /*<<< orphan*/  dst_instance_id; int /*<<< orphan*/  dst_module_id; int /*<<< orphan*/  instance_id; int /*<<< orphan*/  module_id; } ;
struct skl_dev {int /*<<< orphan*/  ipc; } ;
struct TYPE_6__ {int pin_state; } ;
struct TYPE_5__ {int max_input_pins; int max_output_pins; } ;

/* Variables and functions */
 int SKL_PIN_BIND_DONE ; 
 int /*<<< orphan*/  skl_clear_module_state (TYPE_2__*,int,struct skl_module_cfg*) ; 
 int /*<<< orphan*/  skl_dump_bind_info (struct skl_dev*,struct skl_module_cfg*,struct skl_module_cfg*) ; 
 int /*<<< orphan*/  skl_free_queue (TYPE_2__*,int) ; 
 int skl_get_queue_index (TYPE_2__*,struct skl_module_inst_id,int) ; 
 int skl_ipc_bind_unbind (int /*<<< orphan*/ *,struct skl_ipc_bind_unbind_msg*) ; 

int skl_unbind_modules(struct skl_dev *skl,
			struct skl_module_cfg *src_mcfg,
			struct skl_module_cfg *dst_mcfg)
{
	int ret;
	struct skl_ipc_bind_unbind_msg msg;
	struct skl_module_inst_id src_id = src_mcfg->id;
	struct skl_module_inst_id dst_id = dst_mcfg->id;
	int in_max = dst_mcfg->module->max_input_pins;
	int out_max = src_mcfg->module->max_output_pins;
	int src_index, dst_index, src_pin_state, dst_pin_state;

	skl_dump_bind_info(skl, src_mcfg, dst_mcfg);

	/* get src queue index */
	src_index = skl_get_queue_index(src_mcfg->m_out_pin, dst_id, out_max);
	if (src_index < 0)
		return 0;

	msg.src_queue = src_index;

	/* get dst queue index */
	dst_index  = skl_get_queue_index(dst_mcfg->m_in_pin, src_id, in_max);
	if (dst_index < 0)
		return 0;

	msg.dst_queue = dst_index;

	src_pin_state = src_mcfg->m_out_pin[src_index].pin_state;
	dst_pin_state = dst_mcfg->m_in_pin[dst_index].pin_state;

	if (src_pin_state != SKL_PIN_BIND_DONE ||
		dst_pin_state != SKL_PIN_BIND_DONE)
		return 0;

	msg.module_id = src_mcfg->id.module_id;
	msg.instance_id = src_mcfg->id.pvt_id;
	msg.dst_module_id = dst_mcfg->id.module_id;
	msg.dst_instance_id = dst_mcfg->id.pvt_id;
	msg.bind = false;

	ret = skl_ipc_bind_unbind(&skl->ipc, &msg);
	if (!ret) {
		/* free queue only if unbind is success */
		skl_free_queue(src_mcfg->m_out_pin, src_index);
		skl_free_queue(dst_mcfg->m_in_pin, dst_index);

		/*
		 * check only if src module bind state, bind is
		 * always from src -> sink
		 */
		skl_clear_module_state(src_mcfg->m_out_pin, out_max, src_mcfg);
	}

	return ret;
}