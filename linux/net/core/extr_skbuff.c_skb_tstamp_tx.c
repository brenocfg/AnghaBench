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
struct skb_shared_hwtstamps {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCM_TSTAMP_SND ; 
 void __skb_tstamp_tx (struct sk_buff*,struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void skb_tstamp_tx(struct sk_buff *orig_skb,
		   struct skb_shared_hwtstamps *hwtstamps)
{
	return __skb_tstamp_tx(orig_skb, hwtstamps, orig_skb->sk,
			       SCM_TSTAMP_SND);
}