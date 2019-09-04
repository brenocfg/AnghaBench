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
struct sk_buff {int cloned; int /*<<< orphan*/  users; int /*<<< orphan*/  truesize; int /*<<< orphan*/  data; int /*<<< orphan*/  head_frag; int /*<<< orphan*/  head; int /*<<< orphan*/  end; int /*<<< orphan*/  tail; int /*<<< orphan*/ * destructor; int /*<<< orphan*/  pfmemalloc; scalar_t__ peeked; scalar_t__ nohdr; int /*<<< orphan*/  hdr_len; int /*<<< orphan*/  mac_len; int /*<<< orphan*/  data_len; int /*<<< orphan*/  len; int /*<<< orphan*/ * sk; int /*<<< orphan*/ * prev; int /*<<< orphan*/  next; } ;
struct TYPE_2__ {int /*<<< orphan*/  dataref; } ;

/* Variables and functions */
 int /*<<< orphan*/  __copy_skb_header (struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_headroom (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *__skb_clone(struct sk_buff *n, struct sk_buff *skb)
{
#define C(x) n->x = skb->x

	n->next = n->prev = NULL;
	n->sk = NULL;
	__copy_skb_header(n, skb);

	C(len);
	C(data_len);
	C(mac_len);
	n->hdr_len = skb->nohdr ? skb_headroom(skb) : skb->hdr_len;
	n->cloned = 1;
	n->nohdr = 0;
	n->peeked = 0;
	C(pfmemalloc);
	n->destructor = NULL;
	C(tail);
	C(end);
	C(head);
	C(head_frag);
	C(data);
	C(truesize);
	refcount_set(&n->users, 1);

	atomic_inc(&(skb_shinfo(skb)->dataref));
	skb->cloned = 1;

	return n;
#undef C
}