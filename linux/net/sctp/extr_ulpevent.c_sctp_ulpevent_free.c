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
struct sctp_ulpevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_event2skb (struct sctp_ulpevent*) ; 
 scalar_t__ sctp_ulpevent_is_notification (struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  sctp_ulpevent_release_data (struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  sctp_ulpevent_release_owner (struct sctp_ulpevent*) ; 

void sctp_ulpevent_free(struct sctp_ulpevent *event)
{
	if (sctp_ulpevent_is_notification(event))
		sctp_ulpevent_release_owner(event);
	else
		sctp_ulpevent_release_data(event);

	kfree_skb(sctp_event2skb(event));
}