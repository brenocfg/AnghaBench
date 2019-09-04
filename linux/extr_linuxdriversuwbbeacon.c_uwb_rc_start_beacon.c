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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {int /*<<< orphan*/  wEvent; void* bEventType; } ;
struct uwb_rc_evt_confirm {scalar_t__ bResultCode; TYPE_3__ rceb; } ;
struct TYPE_5__ {void* wCommand; void* bCommandType; } ;
struct uwb_rc_cmd_start_beacon {TYPE_2__ rccb; int /*<<< orphan*/  bChannelNumber; void* wBPSTOffset; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct uwb_rc {TYPE_1__ uwb_dev; } ;
typedef  int /*<<< orphan*/  reply ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* UWB_RC_CET_GENERAL ; 
 int /*<<< orphan*/  UWB_RC_CMD_START_BEACON ; 
 scalar_t__ UWB_RC_RES_SUCCESS ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct uwb_rc_cmd_start_beacon*) ; 
 struct uwb_rc_cmd_start_beacon* kzalloc (int,int /*<<< orphan*/ ) ; 
 int uwb_rc_cmd (struct uwb_rc*,char*,TYPE_2__*,int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  uwb_rc_strerror (scalar_t__) ; 

__attribute__((used)) static int uwb_rc_start_beacon(struct uwb_rc *rc, u16 bpst_offset, u8 channel)
{
	int result;
	struct uwb_rc_cmd_start_beacon *cmd;
	struct uwb_rc_evt_confirm reply;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;
	cmd->rccb.bCommandType = UWB_RC_CET_GENERAL;
	cmd->rccb.wCommand = cpu_to_le16(UWB_RC_CMD_START_BEACON);
	cmd->wBPSTOffset = cpu_to_le16(bpst_offset);
	cmd->bChannelNumber = channel;
	reply.rceb.bEventType = UWB_RC_CET_GENERAL;
	reply.rceb.wEvent = UWB_RC_CMD_START_BEACON;
	result = uwb_rc_cmd(rc, "START-BEACON", &cmd->rccb, sizeof(*cmd),
			    &reply.rceb, sizeof(reply));
	if (result < 0)
		goto error_cmd;
	if (reply.bResultCode != UWB_RC_RES_SUCCESS) {
		dev_err(&rc->uwb_dev.dev,
			"START-BEACON: command execution failed: %s (%d)\n",
			uwb_rc_strerror(reply.bResultCode), reply.bResultCode);
		result = -EIO;
	}
error_cmd:
	kfree(cmd);
	return result;
}