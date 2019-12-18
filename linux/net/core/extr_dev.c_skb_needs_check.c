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
struct sk_buff {scalar_t__ ip_summed; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_NONE ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 scalar_t__ CHECKSUM_UNNECESSARY ; 

__attribute__((used)) static inline bool skb_needs_check(struct sk_buff *skb, bool tx_path)
{
	if (tx_path)
		return skb->ip_summed != CHECKSUM_PARTIAL &&
		       skb->ip_summed != CHECKSUM_UNNECESSARY;

	return skb->ip_summed == CHECKSUM_NONE;
}