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
struct sk_buff {int /*<<< orphan*/ * sk; int /*<<< orphan*/ * head; int /*<<< orphan*/  cloned; } ;
struct TYPE_2__ {int /*<<< orphan*/  dataref; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_return (int /*<<< orphan*/ *) ; 
 scalar_t__ is_vmalloc_addr (int /*<<< orphan*/ *) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_rfree (struct sk_buff*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netlink_skb_destructor(struct sk_buff *skb)
{
	if (is_vmalloc_addr(skb->head)) {
		if (!skb->cloned ||
		    !atomic_dec_return(&(skb_shinfo(skb)->dataref)))
			vfree(skb->head);

		skb->head = NULL;
	}
	if (skb->sk != NULL)
		sock_rfree(skb);
}