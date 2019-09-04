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
struct pic32_spi {int /*<<< orphan*/  xfer_done; TYPE_2__* master; int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  fault_irq; } ;
struct TYPE_4__ {TYPE_1__* cur_msg; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pic32_err_stop(struct pic32_spi *pic32s, const char *msg)
{
	/* disable all interrupts */
	disable_irq_nosync(pic32s->fault_irq);
	disable_irq_nosync(pic32s->rx_irq);
	disable_irq_nosync(pic32s->tx_irq);

	/* Show err message and abort xfer with err */
	dev_err(&pic32s->master->dev, "%s\n", msg);
	if (pic32s->master->cur_msg)
		pic32s->master->cur_msg->status = -EIO;
	complete(&pic32s->xfer_done);
}