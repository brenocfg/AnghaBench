#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct ctlr_info {int dummy; } ;
struct ErrorInfo {int CommandStatus; int SenseLen; int ScsiStatus; int /*<<< orphan*/  SenseInfo; } ;
struct CommandList {TYPE_2__* h; struct ErrorInfo* err_info; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
#define  CMD_ABORTED 140 
#define  CMD_ABORT_FAILED 139 
#define  CMD_CONNECTION_LOST 138 
#define  CMD_CTLR_LOCKUP 137 
#define  CMD_DATA_OVERRUN 136 
#define  CMD_DATA_UNDERRUN 135 
#define  CMD_HARDWARE_ERR 134 
#define  CMD_INVALID 133 
#define  CMD_PROTOCOL_ERR 132 
#define  CMD_TARGET_STATUS 131 
#define  CMD_TIMEOUT 130 
#define  CMD_UNABORTABLE 129 
#define  CMD_UNSOLICITED_ABORT 128 
 int SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  decode_sense_data (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int /*<<< orphan*/  hpsa_print_cmd (struct ctlr_info*,char*,struct CommandList*) ; 

__attribute__((used)) static void hpsa_scsi_interpret_error(struct ctlr_info *h,
			struct CommandList *cp)
{
	const struct ErrorInfo *ei = cp->err_info;
	struct device *d = &cp->h->pdev->dev;
	u8 sense_key, asc, ascq;
	int sense_len;

	switch (ei->CommandStatus) {
	case CMD_TARGET_STATUS:
		if (ei->SenseLen > sizeof(ei->SenseInfo))
			sense_len = sizeof(ei->SenseInfo);
		else
			sense_len = ei->SenseLen;
		decode_sense_data(ei->SenseInfo, sense_len,
					&sense_key, &asc, &ascq);
		hpsa_print_cmd(h, "SCSI status", cp);
		if (ei->ScsiStatus == SAM_STAT_CHECK_CONDITION)
			dev_warn(d, "SCSI Status = 02, Sense key = 0x%02x, ASC = 0x%02x, ASCQ = 0x%02x\n",
				sense_key, asc, ascq);
		else
			dev_warn(d, "SCSI Status = 0x%02x\n", ei->ScsiStatus);
		if (ei->ScsiStatus == 0)
			dev_warn(d, "SCSI status is abnormally zero.  "
			"(probably indicates selection timeout "
			"reported incorrectly due to a known "
			"firmware bug, circa July, 2001.)\n");
		break;
	case CMD_DATA_UNDERRUN: /* let mid layer handle it. */
		break;
	case CMD_DATA_OVERRUN:
		hpsa_print_cmd(h, "overrun condition", cp);
		break;
	case CMD_INVALID: {
		/* controller unfortunately reports SCSI passthru's
		 * to non-existent targets as invalid commands.
		 */
		hpsa_print_cmd(h, "invalid command", cp);
		dev_warn(d, "probably means device no longer present\n");
		}
		break;
	case CMD_PROTOCOL_ERR:
		hpsa_print_cmd(h, "protocol error", cp);
		break;
	case CMD_HARDWARE_ERR:
		hpsa_print_cmd(h, "hardware error", cp);
		break;
	case CMD_CONNECTION_LOST:
		hpsa_print_cmd(h, "connection lost", cp);
		break;
	case CMD_ABORTED:
		hpsa_print_cmd(h, "aborted", cp);
		break;
	case CMD_ABORT_FAILED:
		hpsa_print_cmd(h, "abort failed", cp);
		break;
	case CMD_UNSOLICITED_ABORT:
		hpsa_print_cmd(h, "unsolicited abort", cp);
		break;
	case CMD_TIMEOUT:
		hpsa_print_cmd(h, "timed out", cp);
		break;
	case CMD_UNABORTABLE:
		hpsa_print_cmd(h, "unabortable", cp);
		break;
	case CMD_CTLR_LOCKUP:
		hpsa_print_cmd(h, "controller lockup detected", cp);
		break;
	default:
		hpsa_print_cmd(h, "unknown status", cp);
		dev_warn(d, "Unknown command status %x\n",
				ei->CommandStatus);
	}
}