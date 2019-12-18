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
struct sctp_pdapi_event {int pdapi_length; int /*<<< orphan*/  pdapi_assoc_id; void* pdapi_indication; void* pdapi_seq; void* pdapi_stream; void* pdapi_flags; int /*<<< orphan*/  pdapi_type; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  void* __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NOTIFICATION ; 
 int /*<<< orphan*/  SCTP_PARTIAL_DELIVERY_EVENT ; 
 int /*<<< orphan*/  sctp_assoc2id (struct sctp_association const*) ; 
 struct sk_buff* sctp_event2skb (struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_ulpevent_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpevent_set_owner (struct sctp_ulpevent*,struct sctp_association const*) ; 
 struct sctp_pdapi_event* skb_put (struct sk_buff*,int) ; 

struct sctp_ulpevent *sctp_ulpevent_make_pdapi(
					const struct sctp_association *asoc,
					__u32 indication, __u32 sid, __u32 seq,
					__u32 flags, gfp_t gfp)
{
	struct sctp_ulpevent *event;
	struct sctp_pdapi_event *pd;
	struct sk_buff *skb;

	event = sctp_ulpevent_new(sizeof(struct sctp_pdapi_event),
				  MSG_NOTIFICATION, gfp);
	if (!event)
		goto fail;

	skb = sctp_event2skb(event);
	pd = skb_put(skb, sizeof(struct sctp_pdapi_event));

	/* pdapi_type
	 *   It should be SCTP_PARTIAL_DELIVERY_EVENT
	 *
	 * pdapi_flags: 16 bits (unsigned integer)
	 *   Currently unused.
	 */
	pd->pdapi_type = SCTP_PARTIAL_DELIVERY_EVENT;
	pd->pdapi_flags = flags;
	pd->pdapi_stream = sid;
	pd->pdapi_seq = seq;

	/* pdapi_length: 32 bits (unsigned integer)
	 *
	 * This field is the total length of the notification data, including
	 * the notification header.  It will generally be sizeof (struct
	 * sctp_pdapi_event).
	 */
	pd->pdapi_length = sizeof(struct sctp_pdapi_event);

	/*  pdapi_indication: 32 bits (unsigned integer)
	 *
	 * This field holds the indication being sent to the application.
	 */
	pd->pdapi_indication = indication;

	/*  pdapi_assoc_id: sizeof (sctp_assoc_t)
	 *
	 * The association id field, holds the identifier for the association.
	 */
	sctp_ulpevent_set_owner(event, asoc);
	pd->pdapi_assoc_id = sctp_assoc2id(asoc);

	return event;
fail:
	return NULL;
}