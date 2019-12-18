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
struct sctp_transport {scalar_t__ rto; int /*<<< orphan*/  reconf_timer; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sctp_transport_hold (struct sctp_transport*) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

void sctp_transport_reset_reconf_timer(struct sctp_transport *transport)
{
	if (!timer_pending(&transport->reconf_timer))
		if (!mod_timer(&transport->reconf_timer,
			       jiffies + transport->rto))
			sctp_transport_hold(transport);
}