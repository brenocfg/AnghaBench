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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct sk_buff {int dummy; } ;
struct sadb_msg {int sadb_msg_len; scalar_t__ sadb_msg_reserved; int /*<<< orphan*/  sadb_msg_satype; scalar_t__ sadb_msg_errno; int /*<<< orphan*/  sadb_msg_version; int /*<<< orphan*/  sadb_msg_pid; int /*<<< orphan*/  sadb_msg_seq; int /*<<< orphan*/  sadb_msg_type; } ;
struct km_event {int /*<<< orphan*/  net; int /*<<< orphan*/  portid; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROADCAST_ALL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PF_KEY_V2 ; 
 int /*<<< orphan*/  SADB_SATYPE_UNSPEC ; 
 int /*<<< orphan*/  SADB_X_SPDFLUSH ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfkey_broadcast (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sadb_msg* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int key_notify_policy_flush(const struct km_event *c)
{
	struct sk_buff *skb_out;
	struct sadb_msg *hdr;

	skb_out = alloc_skb(sizeof(struct sadb_msg) + 16, GFP_ATOMIC);
	if (!skb_out)
		return -ENOBUFS;
	hdr = skb_put(skb_out, sizeof(struct sadb_msg));
	hdr->sadb_msg_type = SADB_X_SPDFLUSH;
	hdr->sadb_msg_seq = c->seq;
	hdr->sadb_msg_pid = c->portid;
	hdr->sadb_msg_version = PF_KEY_V2;
	hdr->sadb_msg_errno = (uint8_t) 0;
	hdr->sadb_msg_satype = SADB_SATYPE_UNSPEC;
	hdr->sadb_msg_len = (sizeof(struct sadb_msg) / sizeof(uint64_t));
	hdr->sadb_msg_reserved = 0;
	pfkey_broadcast(skb_out, GFP_ATOMIC, BROADCAST_ALL, NULL, c->net);
	return 0;

}