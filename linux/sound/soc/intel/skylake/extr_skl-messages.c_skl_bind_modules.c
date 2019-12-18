#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct skl_module_iface {TYPE_2__* outputs; TYPE_1__* inputs; } ;
struct skl_module_fmt {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  pvt_id; int /*<<< orphan*/  module_id; } ;
struct skl_module_cfg {scalar_t__ m_state; scalar_t__ m_type; size_t fmt_idx; TYPE_4__* m_in_pin; TYPE_4__* m_out_pin; TYPE_3__ id; struct skl_module* module; } ;
struct skl_module {int max_input_pins; int max_output_pins; struct skl_module_iface* formats; } ;
struct skl_ipc_bind_unbind_msg {int src_queue; int dst_queue; int bind; int /*<<< orphan*/  dst_instance_id; int /*<<< orphan*/  dst_module_id; int /*<<< orphan*/  instance_id; int /*<<< orphan*/  module_id; } ;
struct skl_dev {int /*<<< orphan*/  ipc; int /*<<< orphan*/  dev; } ;
struct skl_cpr_pin_fmt {int sink_id; int /*<<< orphan*/  dst_fmt; int /*<<< orphan*/  src_fmt; } ;
struct TYPE_9__ {void* pin_state; } ;
struct TYPE_7__ {struct skl_module_fmt fmt; } ;
struct TYPE_6__ {struct skl_module_fmt fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPR_SINK_FMT_PARAM_ID ; 
 int EINVAL ; 
 scalar_t__ SKL_MODULE_BIND_DONE ; 
 scalar_t__ SKL_MODULE_INIT_DONE ; 
 scalar_t__ SKL_MODULE_TYPE_COPIER ; 
 void* SKL_PIN_BIND_DONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  fill_pin_params (int /*<<< orphan*/ *,struct skl_module_fmt*) ; 
 int skl_alloc_queue (TYPE_4__*,struct skl_module_cfg*,int) ; 
 int /*<<< orphan*/  skl_dump_bind_info (struct skl_dev*,struct skl_module_cfg*,struct skl_module_cfg*) ; 
 int /*<<< orphan*/  skl_free_queue (TYPE_4__*,int) ; 
 int skl_ipc_bind_unbind (int /*<<< orphan*/ *,struct skl_ipc_bind_unbind_msg*) ; 
 int skl_set_module_params (struct skl_dev*,void*,int,int /*<<< orphan*/ ,struct skl_module_cfg*) ; 

int skl_bind_modules(struct skl_dev *skl,
			struct skl_module_cfg *src_mcfg,
			struct skl_module_cfg *dst_mcfg)
{
	int ret = 0;
	struct skl_ipc_bind_unbind_msg msg;
	int in_max = dst_mcfg->module->max_input_pins;
	int out_max = src_mcfg->module->max_output_pins;
	int src_index, dst_index;
	struct skl_module_fmt *format;
	struct skl_cpr_pin_fmt pin_fmt;
	struct skl_module *module;
	struct skl_module_iface *fmt;

	skl_dump_bind_info(skl, src_mcfg, dst_mcfg);

	if (src_mcfg->m_state < SKL_MODULE_INIT_DONE ||
		dst_mcfg->m_state < SKL_MODULE_INIT_DONE)
		return 0;

	src_index = skl_alloc_queue(src_mcfg->m_out_pin, dst_mcfg, out_max);
	if (src_index < 0)
		return -EINVAL;

	msg.src_queue = src_index;
	dst_index = skl_alloc_queue(dst_mcfg->m_in_pin, src_mcfg, in_max);
	if (dst_index < 0) {
		skl_free_queue(src_mcfg->m_out_pin, src_index);
		return -EINVAL;
	}

	/*
	 * Copier module requires the separate large_config_set_ipc to
	 * configure the pins other than 0
	 */
	if (src_mcfg->m_type == SKL_MODULE_TYPE_COPIER && src_index > 0) {
		pin_fmt.sink_id = src_index;
		module = src_mcfg->module;
		fmt = &module->formats[src_mcfg->fmt_idx];

		/* Input fmt is same as that of src module input cfg */
		format = &fmt->inputs[0].fmt;
		fill_pin_params(&(pin_fmt.src_fmt), format);

		format = &fmt->outputs[src_index].fmt;
		fill_pin_params(&(pin_fmt.dst_fmt), format);
		ret = skl_set_module_params(skl, (void *)&pin_fmt,
					sizeof(struct skl_cpr_pin_fmt),
					CPR_SINK_FMT_PARAM_ID, src_mcfg);

		if (ret < 0)
			goto out;
	}

	msg.dst_queue = dst_index;

	dev_dbg(skl->dev, "src queue = %d dst queue =%d\n",
			 msg.src_queue, msg.dst_queue);

	msg.module_id = src_mcfg->id.module_id;
	msg.instance_id = src_mcfg->id.pvt_id;
	msg.dst_module_id = dst_mcfg->id.module_id;
	msg.dst_instance_id = dst_mcfg->id.pvt_id;
	msg.bind = true;

	ret = skl_ipc_bind_unbind(&skl->ipc, &msg);

	if (!ret) {
		src_mcfg->m_state = SKL_MODULE_BIND_DONE;
		src_mcfg->m_out_pin[src_index].pin_state = SKL_PIN_BIND_DONE;
		dst_mcfg->m_in_pin[dst_index].pin_state = SKL_PIN_BIND_DONE;
		return ret;
	}
out:
	/* error case , if IPC fails, clear the queue index */
	skl_free_queue(src_mcfg->m_out_pin, src_index);
	skl_free_queue(dst_mcfg->m_in_pin, dst_index);

	return ret;
}