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
struct sk_buff {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int NET_XMIT_CN ; 
 int /*<<< orphan*/  __qdisc_drop (struct sk_buff*,struct sk_buff**) ; 

__attribute__((used)) static int noop_enqueue(struct sk_buff *skb, struct Qdisc *qdisc,
			struct sk_buff **to_free)
{
	__qdisc_drop(skb, to_free);
	return NET_XMIT_CN;
}