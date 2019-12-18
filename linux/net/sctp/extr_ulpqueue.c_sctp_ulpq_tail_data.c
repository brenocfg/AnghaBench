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
struct sctp_ulpevent {int msg_flags; int /*<<< orphan*/  ppid; int /*<<< orphan*/  ssn; } ;
struct TYPE_4__ {TYPE_1__* data_hdr; } ;
struct sctp_chunk {TYPE_2__ subh; int /*<<< orphan*/  asoc; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_3__ {int /*<<< orphan*/  ppid; int /*<<< orphan*/  ssn; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MSG_EOR ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_event2skb (struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_ulpevent_make_rcvmsg (int /*<<< orphan*/ ,struct sctp_chunk*,int /*<<< orphan*/ ) ; 
 struct sctp_ulpevent* sctp_ulpq_order (struct sctp_ulpq*,struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_ulpq_reasm (struct sctp_ulpq*,struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  sctp_ulpq_tail_event (struct sctp_ulpq*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_head_init (struct sk_buff_head*) ; 

int sctp_ulpq_tail_data(struct sctp_ulpq *ulpq, struct sctp_chunk *chunk,
			gfp_t gfp)
{
	struct sk_buff_head temp;
	struct sctp_ulpevent *event;
	int event_eor = 0;

	/* Create an event from the incoming chunk. */
	event = sctp_ulpevent_make_rcvmsg(chunk->asoc, chunk, gfp);
	if (!event)
		return -ENOMEM;

	event->ssn = ntohs(chunk->subh.data_hdr->ssn);
	event->ppid = chunk->subh.data_hdr->ppid;

	/* Do reassembly if needed.  */
	event = sctp_ulpq_reasm(ulpq, event);

	/* Do ordering if needed.  */
	if (event) {
		/* Create a temporary list to collect chunks on.  */
		skb_queue_head_init(&temp);
		__skb_queue_tail(&temp, sctp_event2skb(event));

		if (event->msg_flags & MSG_EOR)
			event = sctp_ulpq_order(ulpq, event);
	}

	/* Send event to the ULP.  'event' is the sctp_ulpevent for
	 * very first SKB on the 'temp' list.
	 */
	if (event) {
		event_eor = (event->msg_flags & MSG_EOR) ? 1 : 0;
		sctp_ulpq_tail_event(ulpq, &temp);
	}

	return event_eor;
}