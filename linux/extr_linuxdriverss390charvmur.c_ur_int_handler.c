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
struct urdev {int /*<<< orphan*/  io_done; int /*<<< orphan*/  io_request_rc; } ;
struct TYPE_3__ {int dstat; int /*<<< orphan*/  count; int /*<<< orphan*/  cstat; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct irb {TYPE_2__ scsw; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DEV_STAT_CHN_END ; 
 int DEV_STAT_DEV_END ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ IS_ERR (struct irb*) ; 
 int /*<<< orphan*/  PTR_ERR (struct irb*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 struct urdev* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ur_int_handler(struct ccw_device *cdev, unsigned long intparm,
			   struct irb *irb)
{
	struct urdev *urd;

	if (!IS_ERR(irb)) {
		TRACE("ur_int_handler: intparm=0x%lx cstat=%02x dstat=%02x res=%u\n",
		      intparm, irb->scsw.cmd.cstat, irb->scsw.cmd.dstat,
		      irb->scsw.cmd.count);
	}
	if (!intparm) {
		TRACE("ur_int_handler: unsolicited interrupt\n");
		return;
	}
	urd = dev_get_drvdata(&cdev->dev);
	BUG_ON(!urd);
	/* On special conditions irb is an error pointer */
	if (IS_ERR(irb))
		urd->io_request_rc = PTR_ERR(irb);
	else if (irb->scsw.cmd.dstat == (DEV_STAT_CHN_END | DEV_STAT_DEV_END))
		urd->io_request_rc = 0;
	else
		urd->io_request_rc = -EIO;

	complete(urd->io_done);
}