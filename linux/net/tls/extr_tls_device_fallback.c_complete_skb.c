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
struct sock {int /*<<< orphan*/  sk_wmem_alloc; } ;
struct sk_buff {scalar_t__ destructor; int truesize; struct sock* sk; int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refcount_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_sub_and_test (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_copy_header (struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_efree ; 
 int /*<<< orphan*/  update_chksum (struct sk_buff*,int) ; 

__attribute__((used)) static void complete_skb(struct sk_buff *nskb, struct sk_buff *skb, int headln)
{
	struct sock *sk = skb->sk;
	int delta;

	skb_copy_header(nskb, skb);

	skb_put(nskb, skb->len);
	memcpy(nskb->data, skb->data, headln);

	nskb->destructor = skb->destructor;
	nskb->sk = sk;
	skb->destructor = NULL;
	skb->sk = NULL;

	update_chksum(nskb, headln);

	/* sock_efree means skb must gone through skb_orphan_partial() */
	if (nskb->destructor == sock_efree)
		return;

	delta = nskb->truesize - skb->truesize;
	if (likely(delta < 0))
		WARN_ON_ONCE(refcount_sub_and_test(-delta, &sk->sk_wmem_alloc));
	else if (delta)
		refcount_add(delta, &sk->sk_wmem_alloc);
}