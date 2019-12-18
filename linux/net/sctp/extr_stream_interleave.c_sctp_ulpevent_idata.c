#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff_head {int dummy; } ;
struct sctp_ulpq {int dummy; } ;
struct sctp_ulpevent {int msg_flags; void* fsn; int /*<<< orphan*/  ppid; void* mid; } ;
struct TYPE_4__ {TYPE_1__* idata_hdr; } ;
struct sctp_chunk {TYPE_2__ subh; int /*<<< orphan*/  asoc; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_3__ {int /*<<< orphan*/  fsn; int /*<<< orphan*/  ppid; int /*<<< orphan*/  mid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MSG_EOR ; 
 int SCTP_DATA_FIRST_FRAG ; 
 int SCTP_DATA_UNORDERED ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,int /*<<< orphan*/ ) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_enqueue_event (struct sctp_ulpq*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  sctp_event2skb (struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_intl_order (struct sctp_ulpq*,struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_intl_reasm (struct sctp_ulpq*,struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_intl_reasm_uo (struct sctp_ulpq*,struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_ulpevent_make_rcvmsg (int /*<<< orphan*/ ,struct sctp_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (struct sk_buff_head*) ; 

__attribute__((used)) static int sctp_ulpevent_idata(struct sctp_ulpq *ulpq,
			       struct sctp_chunk *chunk, gfp_t gfp)
{
	struct sctp_ulpevent *event;
	struct sk_buff_head temp;
	int event_eor = 0;

	event = sctp_ulpevent_make_rcvmsg(chunk->asoc, chunk, gfp);
	if (!event)
		return -ENOMEM;

	event->mid = ntohl(chunk->subh.idata_hdr->mid);
	if (event->msg_flags & SCTP_DATA_FIRST_FRAG)
		event->ppid = chunk->subh.idata_hdr->ppid;
	else
		event->fsn = ntohl(chunk->subh.idata_hdr->fsn);

	if (!(event->msg_flags & SCTP_DATA_UNORDERED)) {
		event = sctp_intl_reasm(ulpq, event);
		if (event) {
			skb_queue_head_init(&temp);
			__skb_queue_tail(&temp, sctp_event2skb(event));

			if (event->msg_flags & MSG_EOR)
				event = sctp_intl_order(ulpq, event);
		}
	} else {
		event = sctp_intl_reasm_uo(ulpq, event);
		if (event) {
			skb_queue_head_init(&temp);
			__skb_queue_tail(&temp, sctp_event2skb(event));
		}
	}

	if (event) {
		event_eor = (event->msg_flags & MSG_EOR) ? 1 : 0;
		sctp_enqueue_event(ulpq, &temp);
	}

	return event_eor;
}