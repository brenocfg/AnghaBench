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
struct TYPE_2__ {int /*<<< orphan*/  sn_type; } ;
union sctp_notification {TYPE_1__ sn_header; } ;
struct sk_buff {scalar_t__ data; } ;
struct sctp_ulpevent {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 struct sk_buff* sctp_event2skb (struct sctp_ulpevent const*) ; 

__u16 sctp_ulpevent_get_notification_type(const struct sctp_ulpevent *event)
{
	union sctp_notification *notification;
	struct sk_buff *skb;

	skb = sctp_event2skb(event);
	notification = (union sctp_notification *) skb->data;
	return notification->sn_header.sn_type;
}