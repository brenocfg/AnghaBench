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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ len; } ;
struct ip6_frag_state {unsigned int hlen; unsigned int mtu; unsigned int ptr; int hroom; unsigned short troom; scalar_t__ offset; scalar_t__ left; int /*<<< orphan*/  frag_id; int /*<<< orphan*/  nexthdr; int /*<<< orphan*/ * prevhdr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */

void ip6_frag_init(struct sk_buff *skb, unsigned int hlen, unsigned int mtu,
		   unsigned short needed_tailroom, int hdr_room, u8 *prevhdr,
		   u8 nexthdr, __be32 frag_id, struct ip6_frag_state *state)
{
	state->prevhdr = prevhdr;
	state->nexthdr = nexthdr;
	state->frag_id = frag_id;

	state->hlen = hlen;
	state->mtu = mtu;

	state->left = skb->len - hlen;	/* Space per frame */
	state->ptr = hlen;		/* Where to start from */

	state->hroom = hdr_room;
	state->troom = needed_tailroom;

	state->offset = 0;
}