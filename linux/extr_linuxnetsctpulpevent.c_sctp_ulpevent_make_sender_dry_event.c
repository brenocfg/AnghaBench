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
struct sctp_sender_dry_event {int sender_dry_length; int /*<<< orphan*/  sender_dry_assoc_id; scalar_t__ sender_dry_flags; int /*<<< orphan*/  sender_dry_type; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NOTIFICATION ; 
 int /*<<< orphan*/  SCTP_SENDER_DRY_EVENT ; 
 int /*<<< orphan*/  sctp_assoc2id (struct sctp_association const*) ; 
 struct sk_buff* sctp_event2skb (struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_ulpevent_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpevent_set_owner (struct sctp_ulpevent*,struct sctp_association const*) ; 
 struct sctp_sender_dry_event* skb_put (struct sk_buff*,int) ; 

struct sctp_ulpevent *sctp_ulpevent_make_sender_dry_event(
	const struct sctp_association *asoc, gfp_t gfp)
{
	struct sctp_ulpevent *event;
	struct sctp_sender_dry_event *sdry;
	struct sk_buff *skb;

	event = sctp_ulpevent_new(sizeof(struct sctp_sender_dry_event),
				  MSG_NOTIFICATION, gfp);
	if (!event)
		return NULL;

	skb = sctp_event2skb(event);
	sdry = skb_put(skb, sizeof(struct sctp_sender_dry_event));

	sdry->sender_dry_type = SCTP_SENDER_DRY_EVENT;
	sdry->sender_dry_flags = 0;
	sdry->sender_dry_length = sizeof(struct sctp_sender_dry_event);
	sctp_ulpevent_set_owner(event, asoc);
	sdry->sender_dry_assoc_id = sctp_assoc2id(asoc);

	return event;
}