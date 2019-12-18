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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  cb; } ;
struct br_input_skb_cb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  frag_max_size; } ;

/* Variables and functions */
 TYPE_1__* BR_INPUT_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct br_input_skb_cb const*,int) ; 

__attribute__((used)) static void br_skb_cb_restore(struct sk_buff *skb,
			      const struct br_input_skb_cb *cb,
			      u16 fragsz)
{
	memcpy(skb->cb, cb, sizeof(*cb));
	BR_INPUT_SKB_CB(skb)->frag_max_size = fragsz;
}