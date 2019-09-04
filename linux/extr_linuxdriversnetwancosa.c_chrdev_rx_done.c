#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct channel_data {int rx_status; int /*<<< orphan*/  rxwaitq; int /*<<< orphan*/  wsem; int /*<<< orphan*/  rxdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int chrdev_rx_done(struct channel_data *chan)
{
	if (chan->rx_status) { /* Reader has died */
		kfree(chan->rxdata);
		up(&chan->wsem);
	}
	chan->rx_status = 1;
	wake_up_interruptible(&chan->rxwaitq);
	return 1;
}