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
struct sk_buff_head {int dummy; } ;
struct sk_buff {scalar_t__ len; } ;
struct sctp_ulpevent {int dummy; } ;

/* Variables and functions */
 struct sctp_ulpevent* sctp_skb2event (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_ulpevent_free (struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  sctp_ulpevent_is_notification (struct sctp_ulpevent*) ; 
 struct sk_buff* skb_dequeue (struct sk_buff_head*) ; 

unsigned int sctp_queue_purge_ulpevents(struct sk_buff_head *list)
{
	struct sk_buff *skb;
	unsigned int data_unread = 0;

	while ((skb = skb_dequeue(list)) != NULL) {
		struct sctp_ulpevent *event = sctp_skb2event(skb);

		if (!sctp_ulpevent_is_notification(event))
			data_unread += skb->len;

		sctp_ulpevent_free(event);
	}

	return data_unread;
}