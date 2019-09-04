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
typedef  unsigned long long u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ ee_info; scalar_t__ ee_data; } ;
struct sock_exterr_skb {TYPE_1__ ee; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 struct sock_exterr_skb* SKB_EXT_ERR (struct sk_buff*) ; 

__attribute__((used)) static bool skb_zerocopy_notify_extend(struct sk_buff *skb, u32 lo, u16 len)
{
	struct sock_exterr_skb *serr = SKB_EXT_ERR(skb);
	u32 old_lo, old_hi;
	u64 sum_len;

	old_lo = serr->ee.ee_info;
	old_hi = serr->ee.ee_data;
	sum_len = old_hi - old_lo + 1ULL + len;

	if (sum_len >= (1ULL << 32))
		return false;

	if (lo != old_hi + 1)
		return false;

	serr->ee.ee_data += len;
	return true;
}