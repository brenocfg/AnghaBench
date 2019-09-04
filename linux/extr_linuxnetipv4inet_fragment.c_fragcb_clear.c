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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  rbnode; } ;
struct TYPE_2__ {int /*<<< orphan*/  frag_run_len; int /*<<< orphan*/ * next_frag; } ;

/* Variables and functions */
 TYPE_1__* FRAG_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fragcb_clear(struct sk_buff *skb)
{
	RB_CLEAR_NODE(&skb->rbnode);
	FRAG_CB(skb)->next_frag = NULL;
	FRAG_CB(skb)->frag_run_len = skb->len;
}