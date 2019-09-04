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
struct mport_cdev_priv {int /*<<< orphan*/  event_fifo; int /*<<< orphan*/  event_rx_wait; } ;
struct file {struct mport_cdev_priv* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 scalar_t__ kfifo_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t mport_cdev_poll(struct file *filp, poll_table *wait)
{
	struct mport_cdev_priv *priv = filp->private_data;

	poll_wait(filp, &priv->event_rx_wait, wait);
	if (kfifo_len(&priv->event_fifo))
		return EPOLLIN | EPOLLRDNORM;

	return 0;
}