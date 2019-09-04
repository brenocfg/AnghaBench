#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tipc_msg {int dummy; } ;
struct sk_buff {int truesize; int len; } ;
struct TYPE_2__ {int validated; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_HEADROOM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_H_SIZE ; 
 int MIN_H_SIZE ; 
 int TIPC_MAX_USER_MSG_SIZE ; 
 TYPE_1__* TIPC_SKB_CB (struct sk_buff*) ; 
 scalar_t__ TIPC_VERSION ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int buf_roundup_len (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int msg_hdr_sz (struct tipc_msg*) ; 
 int msg_size (struct tipc_msg*) ; 
 scalar_t__ msg_version (struct tipc_msg*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

bool tipc_msg_validate(struct sk_buff **_skb)
{
	struct sk_buff *skb = *_skb;
	struct tipc_msg *hdr;
	int msz, hsz;

	/* Ensure that flow control ratio condition is satisfied */
	if (unlikely(skb->truesize / buf_roundup_len(skb) >= 4)) {
		skb = skb_copy_expand(skb, BUF_HEADROOM, 0, GFP_ATOMIC);
		if (!skb)
			return false;
		kfree_skb(*_skb);
		*_skb = skb;
	}

	if (unlikely(TIPC_SKB_CB(skb)->validated))
		return true;
	if (unlikely(!pskb_may_pull(skb, MIN_H_SIZE)))
		return false;

	hsz = msg_hdr_sz(buf_msg(skb));
	if (unlikely(hsz < MIN_H_SIZE) || (hsz > MAX_H_SIZE))
		return false;
	if (unlikely(!pskb_may_pull(skb, hsz)))
		return false;

	hdr = buf_msg(skb);
	if (unlikely(msg_version(hdr) != TIPC_VERSION))
		return false;

	msz = msg_size(hdr);
	if (unlikely(msz < hsz))
		return false;
	if (unlikely((msz - hsz) > TIPC_MAX_USER_MSG_SIZE))
		return false;
	if (unlikely(skb->len < msz))
		return false;

	TIPC_SKB_CB(skb)->validated = true;
	return true;
}