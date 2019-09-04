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
struct sctp_authkey_event {int auth_length; int /*<<< orphan*/  auth_assoc_id; int /*<<< orphan*/  auth_indication; scalar_t__ auth_altkeynumber; int /*<<< orphan*/  auth_keynumber; scalar_t__ auth_flags; int /*<<< orphan*/  auth_type; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NOTIFICATION ; 
 int /*<<< orphan*/  SCTP_AUTHENTICATION_EVENT ; 
 int /*<<< orphan*/  sctp_assoc2id (struct sctp_association const*) ; 
 struct sk_buff* sctp_event2skb (struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_ulpevent_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpevent_set_owner (struct sctp_ulpevent*,struct sctp_association const*) ; 
 struct sctp_authkey_event* skb_put (struct sk_buff*,int) ; 

struct sctp_ulpevent *sctp_ulpevent_make_authkey(
	const struct sctp_association *asoc, __u16 key_id,
	__u32 indication, gfp_t gfp)
{
	struct sctp_ulpevent *event;
	struct sctp_authkey_event *ak;
	struct sk_buff *skb;

	event = sctp_ulpevent_new(sizeof(struct sctp_authkey_event),
				  MSG_NOTIFICATION, gfp);
	if (!event)
		goto fail;

	skb = sctp_event2skb(event);
	ak = skb_put(skb, sizeof(struct sctp_authkey_event));

	ak->auth_type = SCTP_AUTHENTICATION_EVENT;
	ak->auth_flags = 0;
	ak->auth_length = sizeof(struct sctp_authkey_event);

	ak->auth_keynumber = key_id;
	ak->auth_altkeynumber = 0;
	ak->auth_indication = indication;

	/*
	 * The association id field, holds the identifier for the association.
	 */
	sctp_ulpevent_set_owner(event, asoc);
	ak->auth_assoc_id = sctp_assoc2id(asoc);

	return event;
fail:
	return NULL;
}