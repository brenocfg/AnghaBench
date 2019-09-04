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
struct neighbour {int dummy; } ;

/* Variables and functions */
 int dev_queue_xmit (struct sk_buff*) ; 

int neigh_direct_output(struct neighbour *neigh, struct sk_buff *skb)
{
	return dev_queue_xmit(skb);
}