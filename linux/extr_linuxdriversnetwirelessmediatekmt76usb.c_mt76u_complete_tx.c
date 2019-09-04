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
struct urb {int /*<<< orphan*/  status; struct mt76u_buf* context; } ;
struct mt76u_buf {int done; struct mt76_dev* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_tasklet; } ;
struct mt76_dev {TYPE_1__ usb; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mt76u_urb_error (struct urb*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt76u_complete_tx(struct urb *urb)
{
	struct mt76u_buf *buf = urb->context;
	struct mt76_dev *dev = buf->dev;

	if (mt76u_urb_error(urb))
		dev_err(dev->dev, "tx urb failed: %d\n", urb->status);
	buf->done = true;

	tasklet_schedule(&dev->usb.tx_tasklet);
}