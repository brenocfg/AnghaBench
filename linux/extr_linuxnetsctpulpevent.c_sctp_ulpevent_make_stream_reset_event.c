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
struct sk_buff {int dummy; } ;
struct sctp_ulpevent {int dummy; } ;
struct sctp_stream_reset_event {int strreset_flags; int strreset_length; int /*<<< orphan*/ * strreset_stream_list; int /*<<< orphan*/  strreset_assoc_id; int /*<<< orphan*/  strreset_type; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int __u16 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NOTIFICATION ; 
 int /*<<< orphan*/  SCTP_STREAM_RESET_EVENT ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_assoc2id (struct sctp_association const*) ; 
 struct sk_buff* sctp_event2skb (struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_ulpevent_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpevent_set_owner (struct sctp_ulpevent*,struct sctp_association const*) ; 
 struct sctp_stream_reset_event* skb_put (struct sk_buff*,int) ; 

struct sctp_ulpevent *sctp_ulpevent_make_stream_reset_event(
	const struct sctp_association *asoc, __u16 flags, __u16 stream_num,
	__be16 *stream_list, gfp_t gfp)
{
	struct sctp_stream_reset_event *sreset;
	struct sctp_ulpevent *event;
	struct sk_buff *skb;
	int length, i;

	length = sizeof(struct sctp_stream_reset_event) + 2 * stream_num;
	event = sctp_ulpevent_new(length, MSG_NOTIFICATION, gfp);
	if (!event)
		return NULL;

	skb = sctp_event2skb(event);
	sreset = skb_put(skb, length);

	sreset->strreset_type = SCTP_STREAM_RESET_EVENT;
	sreset->strreset_flags = flags;
	sreset->strreset_length = length;
	sctp_ulpevent_set_owner(event, asoc);
	sreset->strreset_assoc_id = sctp_assoc2id(asoc);

	for (i = 0; i < stream_num; i++)
		sreset->strreset_stream_list[i] = ntohs(stream_list[i]);

	return event;
}