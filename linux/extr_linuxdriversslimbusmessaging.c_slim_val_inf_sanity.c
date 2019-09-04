#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct slim_val_inf {int num_bytes; int start_offset; int /*<<< orphan*/ * wbuf; int /*<<< orphan*/ * rbuf; } ;
struct slim_controller {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SLIM_MSG_MC_CHANGE_VALUE 133 
#define  SLIM_MSG_MC_CLEAR_INFORMATION 132 
#define  SLIM_MSG_MC_REQUEST_CHANGE_VALUE 131 
#define  SLIM_MSG_MC_REQUEST_CLEAR_INFORMATION 130 
#define  SLIM_MSG_MC_REQUEST_INFORMATION 129 
#define  SLIM_MSG_MC_REQUEST_VALUE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int slim_val_inf_sanity(struct slim_controller *ctrl,
			       struct slim_val_inf *msg, u8 mc)
{
	if (!msg || msg->num_bytes > 16 ||
	    (msg->start_offset + msg->num_bytes) > 0xC00)
		goto reterr;
	switch (mc) {
	case SLIM_MSG_MC_REQUEST_VALUE:
	case SLIM_MSG_MC_REQUEST_INFORMATION:
		if (msg->rbuf != NULL)
			return 0;
		break;

	case SLIM_MSG_MC_CHANGE_VALUE:
	case SLIM_MSG_MC_CLEAR_INFORMATION:
		if (msg->wbuf != NULL)
			return 0;
		break;

	case SLIM_MSG_MC_REQUEST_CHANGE_VALUE:
	case SLIM_MSG_MC_REQUEST_CLEAR_INFORMATION:
		if (msg->rbuf != NULL && msg->wbuf != NULL)
			return 0;
		break;
	}
reterr:
	if (msg)
		dev_err(ctrl->dev, "Sanity check failed:msg:offset:0x%x, mc:%d\n",
			msg->start_offset, mc);
	return -EINVAL;
}