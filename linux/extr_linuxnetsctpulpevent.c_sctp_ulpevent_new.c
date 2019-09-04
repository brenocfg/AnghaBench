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
struct sk_buff {int /*<<< orphan*/  truesize; } ;
struct sctp_ulpevent {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 struct sctp_ulpevent* sctp_skb2event (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_ulpevent_init (struct sctp_ulpevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sctp_ulpevent *sctp_ulpevent_new(int size, __u16 msg_flags,
					       gfp_t gfp)
{
	struct sctp_ulpevent *event;
	struct sk_buff *skb;

	skb = alloc_skb(size, gfp);
	if (!skb)
		goto fail;

	event = sctp_skb2event(skb);
	sctp_ulpevent_init(event, msg_flags, skb->truesize);

	return event;

fail:
	return NULL;
}