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
struct sk_buff {TYPE_1__* sk; scalar_t__ truesize; int /*<<< orphan*/ * destructor; int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk_wmem_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refcount_add (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_copy_header (struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_chksum (struct sk_buff*,int) ; 

__attribute__((used)) static void complete_skb(struct sk_buff *nskb, struct sk_buff *skb, int headln)
{
	skb_copy_header(nskb, skb);

	skb_put(nskb, skb->len);
	memcpy(nskb->data, skb->data, headln);
	update_chksum(nskb, headln);

	nskb->destructor = skb->destructor;
	nskb->sk = skb->sk;
	skb->destructor = NULL;
	skb->sk = NULL;
	refcount_add(nskb->truesize - skb->truesize,
		     &nskb->sk->sk_wmem_alloc);
}