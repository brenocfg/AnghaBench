#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dccph_sport; int /*<<< orphan*/  dccph_dport; } ;
struct TYPE_3__ {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 TYPE_2__* dccp_hdr (struct sk_buff const*) ; 
 TYPE_1__* ip_hdr (struct sk_buff const*) ; 
 int /*<<< orphan*/  secure_dccp_sequence_number (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 dccp_v4_init_sequence(const struct sk_buff *skb)
{
	return secure_dccp_sequence_number(ip_hdr(skb)->daddr,
					   ip_hdr(skb)->saddr,
					   dccp_hdr(skb)->dccph_dport,
					   dccp_hdr(skb)->dccph_sport);
}