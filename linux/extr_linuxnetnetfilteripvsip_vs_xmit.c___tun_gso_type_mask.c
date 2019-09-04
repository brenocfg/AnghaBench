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

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int SKB_GSO_IPXIP4 ; 
 int SKB_GSO_IPXIP6 ; 

__attribute__((used)) static inline int __tun_gso_type_mask(int encaps_af, int orig_af)
{
	switch (encaps_af) {
	case AF_INET:
		return SKB_GSO_IPXIP4;
	case AF_INET6:
		return SKB_GSO_IPXIP6;
	default:
		return 0;
	}
}