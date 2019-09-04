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
typedef  int /*<<< orphan*/  u32 ;
struct typec_altmode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  conf; int /*<<< orphan*/  status; } ;
struct dp_altmode {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; TYPE_1__ data; } ;

/* Variables and functions */
#define  CMDT_RSP_ACK 133 
#define  CMDT_RSP_NAK 132 
#define  CMD_ENTER_MODE 131 
#define  CMD_EXIT_MODE 130 
#define  DP_CMD_CONFIGURE 129 
#define  DP_CMD_STATUS_UPDATE 128 
 scalar_t__ DP_STATE_IDLE ; 
 scalar_t__ DP_STATE_UPDATE ; 
 int EBUSY ; 
 int PD_VDO_CMD (int /*<<< orphan*/  const) ; 
 int PD_VDO_CMDT (int /*<<< orphan*/  const) ; 
 int dp_altmode_configured (struct dp_altmode*) ; 
 int dp_altmode_status_update (struct dp_altmode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct dp_altmode* typec_altmode_get_drvdata (struct typec_altmode*) ; 

__attribute__((used)) static int dp_altmode_vdm(struct typec_altmode *alt,
			  const u32 hdr, const u32 *vdo, int count)
{
	struct dp_altmode *dp = typec_altmode_get_drvdata(alt);
	int cmd_type = PD_VDO_CMDT(hdr);
	int cmd = PD_VDO_CMD(hdr);
	int ret = 0;

	mutex_lock(&dp->lock);

	if (dp->state != DP_STATE_IDLE) {
		ret = -EBUSY;
		goto err_unlock;
	}

	switch (cmd_type) {
	case CMDT_RSP_ACK:
		switch (cmd) {
		case CMD_ENTER_MODE:
			dp->state = DP_STATE_UPDATE;
			break;
		case CMD_EXIT_MODE:
			dp->data.status = 0;
			dp->data.conf = 0;
			break;
		case DP_CMD_STATUS_UPDATE:
			dp->data.status = *vdo;
			ret = dp_altmode_status_update(dp);
			break;
		case DP_CMD_CONFIGURE:
			ret = dp_altmode_configured(dp);
			break;
		default:
			break;
		}
		break;
	case CMDT_RSP_NAK:
		switch (cmd) {
		case DP_CMD_CONFIGURE:
			dp->data.conf = 0;
			ret = dp_altmode_configured(dp);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	if (dp->state != DP_STATE_IDLE)
		schedule_work(&dp->work);

err_unlock:
	mutex_unlock(&dp->lock);
	return ret;
}