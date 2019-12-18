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
 int ICMPV6_NOROUTE ; 
 size_t NFT_REJECT_ICMPX_MAX ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int* icmp_code_v6 ; 

int nft_reject_icmpv6_code(u8 code)
{
	if (WARN_ON_ONCE(code > NFT_REJECT_ICMPX_MAX))
		return ICMPV6_NOROUTE;

	return icmp_code_v6[code];
}