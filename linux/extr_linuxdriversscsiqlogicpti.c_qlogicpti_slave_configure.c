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
typedef  int u_short ;
struct scsi_device {int id; scalar_t__ wdtr; scalar_t__ sdtr; int /*<<< orphan*/  host; } ;
struct qlogicpti {TYPE_1__* dev_param; } ;
struct TYPE_2__ {int device_flags; int synchronous_offset; int synchronous_period; } ;

/* Variables and functions */
 int MBOX_SET_TARGET_PARAMS ; 
 int /*<<< orphan*/  qlogicpti_mbox_command (struct qlogicpti*,int*,int /*<<< orphan*/ ) ; 
 struct qlogicpti* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlogicpti_slave_configure(struct scsi_device *sdev)
{
	struct qlogicpti *qpti = shost_priv(sdev->host);
	int tgt = sdev->id;
	u_short param[6];

	/* tags handled in midlayer */
	/* enable sync mode? */
	if (sdev->sdtr) {
		qpti->dev_param[tgt].device_flags |= 0x10;
	} else {
		qpti->dev_param[tgt].synchronous_offset = 0;
		qpti->dev_param[tgt].synchronous_period = 0;
	}
	/* are we wide capable? */
	if (sdev->wdtr)
		qpti->dev_param[tgt].device_flags |= 0x20;

	param[0] = MBOX_SET_TARGET_PARAMS;
	param[1] = (tgt << 8);
	param[2] = (qpti->dev_param[tgt].device_flags << 8);
	if (qpti->dev_param[tgt].device_flags & 0x10) {
		param[3] = (qpti->dev_param[tgt].synchronous_offset << 8) |
			qpti->dev_param[tgt].synchronous_period;
	} else {
		param[3] = 0;
	}
	qlogicpti_mbox_command(qpti, param, 0);
	return 0;
}