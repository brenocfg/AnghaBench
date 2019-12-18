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
struct sctp_ulpq {TYPE_1__* asoc; } ;
struct sctp_ulpevent {scalar_t__ mid; int /*<<< orphan*/  stream; } ;
struct sctp_stream {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {struct sctp_stream stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  in ; 
 int /*<<< orphan*/  sctp_intl_retrieve_ordered (struct sctp_ulpq*,struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  sctp_intl_store_ordered (struct sctp_ulpq*,struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  sctp_mid_next (struct sctp_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_mid_peek (struct sctp_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sctp_ulpevent *sctp_intl_order(struct sctp_ulpq *ulpq,
					     struct sctp_ulpevent *event)
{
	struct sctp_stream *stream;
	__u16 sid;

	stream  = &ulpq->asoc->stream;
	sid = event->stream;

	if (event->mid != sctp_mid_peek(stream, in, sid)) {
		sctp_intl_store_ordered(ulpq, event);
		return NULL;
	}

	sctp_mid_next(stream, in, sid);

	sctp_intl_retrieve_ordered(ulpq, event);

	return event;
}