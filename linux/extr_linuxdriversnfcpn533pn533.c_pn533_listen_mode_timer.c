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
struct timer_list {int dummy; } ;
struct pn533 {int cancel_listen; int /*<<< orphan*/  poll_work; int /*<<< orphan*/  wq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PN533_POLL_INTERVAL ; 
 struct pn533* dev ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct pn533* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listen_timer ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pn533_poll_next_mod (struct pn533*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pn533_listen_mode_timer(struct timer_list *t)
{
	struct pn533 *dev = from_timer(dev, t, listen_timer);

	dev_dbg(dev->dev, "Listen mode timeout\n");

	dev->cancel_listen = 1;

	pn533_poll_next_mod(dev);

	queue_delayed_work(dev->wq, &dev->poll_work,
			   msecs_to_jiffies(PN533_POLL_INTERVAL));
}