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
struct qlogicpti {TYPE_1__* qhost; int /*<<< orphan*/  qregs; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
struct TYPE_2__ {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int /*<<< orphan*/ ) ; 

const char *qlogicpti_info(struct Scsi_Host *host)
{
	static char buf[80];
	struct qlogicpti *qpti = (struct qlogicpti *) host->hostdata;

	sprintf(buf, "PTI Qlogic,ISP SBUS SCSI irq %d regs at %p",
		qpti->qhost->irq, qpti->qregs);
	return buf;
}