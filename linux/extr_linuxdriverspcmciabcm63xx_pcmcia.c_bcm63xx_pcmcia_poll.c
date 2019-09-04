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
struct timer_list {int dummy; } ;
struct TYPE_2__ {unsigned int csc_mask; } ;
struct bcm63xx_pcmcia_socket {unsigned int old_status; int /*<<< orphan*/  timer; int /*<<< orphan*/  socket; int /*<<< orphan*/  lock; TYPE_1__ requested_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM63XX_PCMCIA_POLL_RATE ; 
 unsigned int __get_socket_status (struct bcm63xx_pcmcia_socket*) ; 
 struct bcm63xx_pcmcia_socket* from_timer (struct bcm63xx_pcmcia_socket*,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_parse_events (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void bcm63xx_pcmcia_poll(struct timer_list *t)
{
	struct bcm63xx_pcmcia_socket *skt;
	unsigned int stat, events;

	skt = from_timer(skt, t, timer);

	spin_lock_bh(&skt->lock);

	stat = __get_socket_status(skt);

	/* keep only changed bits, and mask with required one from the
	 * core */
	events = (stat ^ skt->old_status) & skt->requested_state.csc_mask;
	skt->old_status = stat;
	spin_unlock_bh(&skt->lock);

	if (events)
		pcmcia_parse_events(&skt->socket, events);

	mod_timer(&skt->timer,
		  jiffies + msecs_to_jiffies(BCM63XX_PCMCIA_POLL_RATE));
}