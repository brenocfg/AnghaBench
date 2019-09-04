#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {struct rfcomm_dev* driver_data; } ;
struct rfcomm_dev {int /*<<< orphan*/  port; TYPE_1__* dlc; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFCOMM_TTY_ATTACHED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_dlc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  rfcomm_dlc_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rfcomm_tty_cleanup(struct tty_struct *tty)
{
	struct rfcomm_dev *dev = tty->driver_data;

	clear_bit(RFCOMM_TTY_ATTACHED, &dev->flags);

	rfcomm_dlc_lock(dev->dlc);
	tty->driver_data = NULL;
	rfcomm_dlc_unlock(dev->dlc);

	/*
	 * purge the dlc->tx_queue to avoid circular dependencies
	 * between dev and dlc
	 */
	skb_queue_purge(&dev->dlc->tx_queue);

	tty_port_put(&dev->port);
}