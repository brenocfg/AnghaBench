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
struct sk_buff {int /*<<< orphan*/  destructor; int /*<<< orphan*/ * sk; } ;
struct sctp_chunk {int /*<<< orphan*/  shkey; scalar_t__ auth; struct sk_buff* skb; struct sctp_association* asoc; } ;
struct TYPE_3__ {int /*<<< orphan*/ * sk; } ;
struct sctp_association {TYPE_1__ base; int /*<<< orphan*/  shkey; } ;
struct TYPE_4__ {struct sctp_chunk* destructor_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_auth_shkey_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_control_release_owner ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void sctp_control_set_owner_w(struct sctp_chunk *chunk)
{
	struct sctp_association *asoc = chunk->asoc;
	struct sk_buff *skb = chunk->skb;

	/* TODO: properly account for control chunks.
	 * To do it right we'll need:
	 *  1) endpoint if association isn't known.
	 *  2) proper memory accounting.
	 *
	 *  For now don't do anything for now.
	 */
	if (chunk->auth) {
		chunk->shkey = asoc->shkey;
		sctp_auth_shkey_hold(chunk->shkey);
	}
	skb->sk = asoc ? asoc->base.sk : NULL;
	skb_shinfo(skb)->destructor_arg = chunk;
	skb->destructor = sctp_control_release_owner;
}