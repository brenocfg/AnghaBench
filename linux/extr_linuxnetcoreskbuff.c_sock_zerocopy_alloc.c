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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * user; } ;
struct ubuf_info {int len; size_t bytelen; int zerocopy; int /*<<< orphan*/  refcnt; scalar_t__ id; int /*<<< orphan*/  callback; TYPE_1__ mmp; } ;
struct sock {int /*<<< orphan*/  sk_zckey; } ;
struct sk_buff {scalar_t__ cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_task () ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ mm_account_pinned_pages (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 struct sk_buff* sock_omalloc (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_zerocopy_callback ; 

struct ubuf_info *sock_zerocopy_alloc(struct sock *sk, size_t size)
{
	struct ubuf_info *uarg;
	struct sk_buff *skb;

	WARN_ON_ONCE(!in_task());

	skb = sock_omalloc(sk, 0, GFP_KERNEL);
	if (!skb)
		return NULL;

	BUILD_BUG_ON(sizeof(*uarg) > sizeof(skb->cb));
	uarg = (void *)skb->cb;
	uarg->mmp.user = NULL;

	if (mm_account_pinned_pages(&uarg->mmp, size)) {
		kfree_skb(skb);
		return NULL;
	}

	uarg->callback = sock_zerocopy_callback;
	uarg->id = ((u32)atomic_inc_return(&sk->sk_zckey)) - 1;
	uarg->len = 1;
	uarg->bytelen = size;
	uarg->zerocopy = 1;
	refcount_set(&uarg->refcnt, 1);
	sock_hold(sk);

	return uarg;
}