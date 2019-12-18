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
struct sctp_ulpq {int dummy; } ;
struct sctp_ulpevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_event2skb (struct sctp_ulpevent*) ; 
 int sctp_ulpq_tail_event (struct sctp_ulpq*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_head_init (struct sk_buff_head*) ; 

__attribute__((used)) static int do_ulpq_tail_event(struct sctp_ulpq *ulpq, struct sctp_ulpevent *event)
{
	struct sk_buff_head temp;

	skb_queue_head_init(&temp);
	__skb_queue_tail(&temp, sctp_event2skb(event));
	return sctp_ulpq_tail_event(ulpq, &temp);
}