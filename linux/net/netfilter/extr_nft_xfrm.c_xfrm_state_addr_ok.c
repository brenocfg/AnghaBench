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
typedef  scalar_t__ u8 ;
typedef  enum nft_xfrm_keys { ____Placeholder_nft_xfrm_keys } nft_xfrm_keys ;

/* Variables and functions */
 scalar_t__ NFPROTO_IPV4 ; 
 scalar_t__ NFPROTO_IPV6 ; 
#define  NFT_XFRM_KEY_DADDR_IP4 131 
#define  NFT_XFRM_KEY_DADDR_IP6 130 
#define  NFT_XFRM_KEY_SADDR_IP4 129 
#define  NFT_XFRM_KEY_SADDR_IP6 128 
 scalar_t__ XFRM_MODE_BEET ; 
 scalar_t__ XFRM_MODE_TUNNEL ; 

__attribute__((used)) static bool xfrm_state_addr_ok(enum nft_xfrm_keys k, u8 family, u8 mode)
{
	switch (k) {
	case NFT_XFRM_KEY_DADDR_IP4:
	case NFT_XFRM_KEY_SADDR_IP4:
		if (family == NFPROTO_IPV4)
			break;
		return false;
	case NFT_XFRM_KEY_DADDR_IP6:
	case NFT_XFRM_KEY_SADDR_IP6:
		if (family == NFPROTO_IPV6)
			break;
		return false;
	default:
		return true;
	}

	return mode == XFRM_MODE_BEET || mode == XFRM_MODE_TUNNEL;
}