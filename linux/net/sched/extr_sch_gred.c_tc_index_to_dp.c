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
typedef  int u16 ;
struct sk_buff {int tc_index; } ;

/* Variables and functions */
 int GRED_VQ_MASK ; 

__attribute__((used)) static inline u16 tc_index_to_dp(struct sk_buff *skb)
{
	return skb->tc_index & GRED_VQ_MASK;
}