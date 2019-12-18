#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct sctp_ulpevent {int dummy; } ;
struct sctp_shared_key {int /*<<< orphan*/  key_id; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  key_list; scalar_t__ deactivated; } ;
struct sctp_chunk {struct sctp_shared_key* shkey; struct sctp_association* asoc; } ;
struct TYPE_5__ {TYPE_1__* si; } ;
struct sctp_association {int /*<<< orphan*/  ulpq; TYPE_2__ stream; } ;
struct TYPE_6__ {struct sctp_chunk* destructor_arg; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* enqueue_event ) (int /*<<< orphan*/ *,struct sctp_ulpevent*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SCTP_AUTH_FREE_KEY ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_auth_shkey_release (struct sctp_shared_key*) ; 
 struct sctp_ulpevent* sctp_ulpevent_make_authkey (struct sctp_association*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct sctp_ulpevent*) ; 

__attribute__((used)) static void sctp_control_release_owner(struct sk_buff *skb)
{
	struct sctp_chunk *chunk = skb_shinfo(skb)->destructor_arg;

	if (chunk->shkey) {
		struct sctp_shared_key *shkey = chunk->shkey;
		struct sctp_association *asoc = chunk->asoc;

		/* refcnt == 2 and !list_empty mean after this release, it's
		 * not being used anywhere, and it's time to notify userland
		 * that this shkey can be freed if it's been deactivated.
		 */
		if (shkey->deactivated && !list_empty(&shkey->key_list) &&
		    refcount_read(&shkey->refcnt) == 2) {
			struct sctp_ulpevent *ev;

			ev = sctp_ulpevent_make_authkey(asoc, shkey->key_id,
							SCTP_AUTH_FREE_KEY,
							GFP_KERNEL);
			if (ev)
				asoc->stream.si->enqueue_event(&asoc->ulpq, ev);
		}
		sctp_auth_shkey_release(chunk->shkey);
	}
}