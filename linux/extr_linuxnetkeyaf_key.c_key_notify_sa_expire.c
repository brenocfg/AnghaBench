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
struct TYPE_4__ {int /*<<< orphan*/  proto; } ;
struct xfrm_state {TYPE_2__ id; } ;
struct sk_buff {scalar_t__ data; } ;
struct sadb_msg {scalar_t__ sadb_msg_pid; scalar_t__ sadb_msg_seq; scalar_t__ sadb_msg_reserved; scalar_t__ sadb_msg_errno; int /*<<< orphan*/  sadb_msg_satype; int /*<<< orphan*/  sadb_msg_type; int /*<<< orphan*/  sadb_msg_version; } ;
struct TYPE_3__ {int hard; } ;
struct km_event {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROADCAST_REGISTERED ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  PF_KEY_V2 ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  SADB_EXPIRE ; 
 int /*<<< orphan*/  pfkey_broadcast (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfkey_proto2satype (int /*<<< orphan*/ ) ; 
 struct sk_buff* pfkey_xfrm_state2msg_expire (struct xfrm_state*,int) ; 
 int /*<<< orphan*/  xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int key_notify_sa_expire(struct xfrm_state *x, const struct km_event *c)
{
	struct sk_buff *out_skb;
	struct sadb_msg *out_hdr;
	int hard;
	int hsc;

	hard = c->data.hard;
	if (hard)
		hsc = 2;
	else
		hsc = 1;

	out_skb = pfkey_xfrm_state2msg_expire(x, hsc);
	if (IS_ERR(out_skb))
		return PTR_ERR(out_skb);

	out_hdr = (struct sadb_msg *) out_skb->data;
	out_hdr->sadb_msg_version = PF_KEY_V2;
	out_hdr->sadb_msg_type = SADB_EXPIRE;
	out_hdr->sadb_msg_satype = pfkey_proto2satype(x->id.proto);
	out_hdr->sadb_msg_errno = 0;
	out_hdr->sadb_msg_reserved = 0;
	out_hdr->sadb_msg_seq = 0;
	out_hdr->sadb_msg_pid = 0;

	pfkey_broadcast(out_skb, GFP_ATOMIC, BROADCAST_REGISTERED, NULL,
			xs_net(x));
	return 0;
}