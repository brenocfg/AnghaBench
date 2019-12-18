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
typedef  int /*<<< orphan*/  u8 ;
struct sof_ipc_ctrl_data_params {scalar_t__ pl_size; int /*<<< orphan*/  msg_bytes; int /*<<< orphan*/  num_msg; scalar_t__ hdr_bytes; int /*<<< orphan*/ * dst; int /*<<< orphan*/ * src; } ;
struct sof_ipc_ctrl_data {TYPE_1__* data; scalar_t__ compv; scalar_t__ chanv; } ;
typedef  enum sof_ipc_ctrl_type { ____Placeholder_sof_ipc_ctrl_type } sof_ipc_ctrl_type ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,scalar_t__) ; 
 int EINVAL ; 
#define  SOF_CTRL_TYPE_DATA_GET 133 
#define  SOF_CTRL_TYPE_DATA_SET 132 
#define  SOF_CTRL_TYPE_VALUE_CHAN_GET 131 
#define  SOF_CTRL_TYPE_VALUE_CHAN_SET 130 
#define  SOF_CTRL_TYPE_VALUE_COMP_GET 129 
#define  SOF_CTRL_TYPE_VALUE_COMP_SET 128 
 scalar_t__ SOF_IPC_MSG_MAX_SIZE ; 

__attribute__((used)) static int sof_get_ctrl_copy_params(enum sof_ipc_ctrl_type ctrl_type,
				    struct sof_ipc_ctrl_data *src,
				    struct sof_ipc_ctrl_data *dst,
				    struct sof_ipc_ctrl_data_params *sparams)
{
	switch (ctrl_type) {
	case SOF_CTRL_TYPE_VALUE_CHAN_GET:
	case SOF_CTRL_TYPE_VALUE_CHAN_SET:
		sparams->src = (u8 *)src->chanv;
		sparams->dst = (u8 *)dst->chanv;
		break;
	case SOF_CTRL_TYPE_VALUE_COMP_GET:
	case SOF_CTRL_TYPE_VALUE_COMP_SET:
		sparams->src = (u8 *)src->compv;
		sparams->dst = (u8 *)dst->compv;
		break;
	case SOF_CTRL_TYPE_DATA_GET:
	case SOF_CTRL_TYPE_DATA_SET:
		sparams->src = (u8 *)src->data->data;
		sparams->dst = (u8 *)dst->data->data;
		break;
	default:
		return -EINVAL;
	}

	/* calculate payload size and number of messages */
	sparams->pl_size = SOF_IPC_MSG_MAX_SIZE - sparams->hdr_bytes;
	sparams->num_msg = DIV_ROUND_UP(sparams->msg_bytes, sparams->pl_size);

	return 0;
}