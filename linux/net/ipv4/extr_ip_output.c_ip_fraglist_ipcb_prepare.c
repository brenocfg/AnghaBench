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
struct sk_buff {int dummy; } ;
struct ip_fraglist_iter {scalar_t__ offset; struct sk_buff* frag; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 TYPE_1__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_options_fragment (struct sk_buff*) ; 

__attribute__((used)) static void ip_fraglist_ipcb_prepare(struct sk_buff *skb,
				     struct ip_fraglist_iter *iter)
{
	struct sk_buff *to = iter->frag;

	/* Copy the flags to each fragment. */
	IPCB(to)->flags = IPCB(skb)->flags;

	if (iter->offset == 0)
		ip_options_fragment(to);
}