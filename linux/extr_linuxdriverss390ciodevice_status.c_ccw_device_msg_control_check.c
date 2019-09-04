#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int sch_no; int /*<<< orphan*/  ssid; } ;
struct subchannel {TYPE_4__ schid; } ;
struct irb {int /*<<< orphan*/  scsw; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_3__* private; TYPE_1__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  devno; } ;
struct TYPE_7__ {TYPE_2__ dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_HEX_EVENT (int /*<<< orphan*/ ,struct irb*,int) ; 
 int /*<<< orphan*/  CIO_MSG_EVENT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CIO_TRACE_EVENT (int /*<<< orphan*/ ,char*) ; 
 int SCHN_STAT_CHN_CTRL_CHK ; 
 int SCHN_STAT_CHN_DATA_CHK ; 
 int SCHN_STAT_INTF_CTRL_CHK ; 
 int scsw_cstat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsw_dstat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsw_is_valid_cstat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ccw_device_msg_control_check(struct ccw_device *cdev, struct irb *irb)
{
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	char dbf_text[15];

	if (!scsw_is_valid_cstat(&irb->scsw) ||
	    !(scsw_cstat(&irb->scsw) & (SCHN_STAT_CHN_DATA_CHK |
	      SCHN_STAT_CHN_CTRL_CHK | SCHN_STAT_INTF_CTRL_CHK)))
		return;
	CIO_MSG_EVENT(0, "Channel-Check or Interface-Control-Check "
		      "received"
		      " ... device %04x on subchannel 0.%x.%04x, dev_stat "
		      ": %02X sch_stat : %02X\n",
		      cdev->private->dev_id.devno, sch->schid.ssid,
		      sch->schid.sch_no,
		      scsw_dstat(&irb->scsw), scsw_cstat(&irb->scsw));
	sprintf(dbf_text, "chk%x", sch->schid.sch_no);
	CIO_TRACE_EVENT(0, dbf_text);
	CIO_HEX_EVENT(0, irb, sizeof(struct irb));
}