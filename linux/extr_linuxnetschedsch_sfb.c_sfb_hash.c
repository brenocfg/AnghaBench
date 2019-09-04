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
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {size_t* hashes; } ;

/* Variables and functions */
 TYPE_1__* sfb_skb_cb (struct sk_buff const*) ; 

__attribute__((used)) static u32 sfb_hash(const struct sk_buff *skb, u32 slot)
{
	return sfb_skb_cb(skb)->hashes[slot];
}