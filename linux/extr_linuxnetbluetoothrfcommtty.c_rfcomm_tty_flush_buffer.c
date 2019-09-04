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
struct tty_struct {scalar_t__ driver_data; } ;
struct rfcomm_dev {TYPE_1__* dlc; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct tty_struct*,struct rfcomm_dev*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static void rfcomm_tty_flush_buffer(struct tty_struct *tty)
{
	struct rfcomm_dev *dev = (struct rfcomm_dev *) tty->driver_data;

	BT_DBG("tty %p dev %p", tty, dev);

	if (!dev || !dev->dlc)
		return;

	skb_queue_purge(&dev->dlc->tx_queue);
	tty_wakeup(tty);
}