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
typedef  size_t u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t NFT_REJECT_ICMPX_MAX ; 
 int* icmp_code_v6 ; 

int nft_reject_icmpv6_code(u8 code)
{
	BUG_ON(code > NFT_REJECT_ICMPX_MAX);

	return icmp_code_v6[code];
}