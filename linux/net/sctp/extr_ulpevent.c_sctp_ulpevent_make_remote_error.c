#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  truesize; } ;
struct sctp_ulpevent {int dummy; } ;
struct sctp_remote_error {int /*<<< orphan*/  sre_assoc_id; int /*<<< orphan*/  sre_error; int /*<<< orphan*/  sre_length; scalar_t__ sre_flags; int /*<<< orphan*/  sre_type; } ;
struct sctp_errhdr {int /*<<< orphan*/  length; int /*<<< orphan*/  cause; } ;
struct sctp_chunk {TYPE_1__* skb; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u16 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NOTIFICATION ; 
 int SCTP_PAD4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_REMOTE_ERROR ; 
 int /*<<< orphan*/  memset (struct sctp_remote_error*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_assoc2id (struct sctp_association const*) ; 
 struct sctp_ulpevent* sctp_skb2event (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_ulpevent_init (struct sctp_ulpevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpevent_set_owner (struct sctp_ulpevent*,struct sctp_association const*) ; 
 struct sk_buff* skb_copy_expand (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (TYPE_1__*,int) ; 
 struct sctp_remote_error* skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

struct sctp_ulpevent *
sctp_ulpevent_make_remote_error(const struct sctp_association *asoc,
				struct sctp_chunk *chunk, __u16 flags,
				gfp_t gfp)
{
	struct sctp_remote_error *sre;
	struct sctp_ulpevent *event;
	struct sctp_errhdr *ch;
	struct sk_buff *skb;
	__be16 cause;
	int elen;

	ch = (struct sctp_errhdr *)(chunk->skb->data);
	cause = ch->cause;
	elen = SCTP_PAD4(ntohs(ch->length)) - sizeof(*ch);

	/* Pull off the ERROR header.  */
	skb_pull(chunk->skb, sizeof(*ch));

	/* Copy the skb to a new skb with room for us to prepend
	 * notification with.
	 */
	skb = skb_copy_expand(chunk->skb, sizeof(*sre), 0, gfp);

	/* Pull off the rest of the cause TLV from the chunk.  */
	skb_pull(chunk->skb, elen);
	if (!skb)
		goto fail;

	/* Embed the event fields inside the cloned skb.  */
	event = sctp_skb2event(skb);
	sctp_ulpevent_init(event, MSG_NOTIFICATION, skb->truesize);

	sre = skb_push(skb, sizeof(*sre));

	/* Trim the buffer to the right length.  */
	skb_trim(skb, sizeof(*sre) + elen);

	/* RFC6458, Section 6.1.3. SCTP_REMOTE_ERROR */
	memset(sre, 0, sizeof(*sre));
	sre->sre_type = SCTP_REMOTE_ERROR;
	sre->sre_flags = 0;
	sre->sre_length = skb->len;
	sre->sre_error = cause;
	sctp_ulpevent_set_owner(event, asoc);
	sre->sre_assoc_id = sctp_assoc2id(asoc);

	return event;
fail:
	return NULL;
}