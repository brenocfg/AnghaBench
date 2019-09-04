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
typedef  int u8 ;
struct efx_filter_spec {int match_flags; scalar_t__ ether_type; int /*<<< orphan*/ * loc_host; int /*<<< orphan*/  loc_mac; } ;

/* Variables and functions */
 int EFX_FILTER_MATCH_ETHER_TYPE ; 
 int EFX_FILTER_MATCH_LOC_HOST ; 
 int EFX_FILTER_MATCH_LOC_MAC ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool efx_ef10_filter_is_exclusive(const struct efx_filter_spec *spec)
{
	if (spec->match_flags & EFX_FILTER_MATCH_LOC_MAC &&
	    !is_multicast_ether_addr(spec->loc_mac))
		return true;

	if ((spec->match_flags &
	     (EFX_FILTER_MATCH_ETHER_TYPE | EFX_FILTER_MATCH_LOC_HOST)) ==
	    (EFX_FILTER_MATCH_ETHER_TYPE | EFX_FILTER_MATCH_LOC_HOST)) {
		if (spec->ether_type == htons(ETH_P_IP) &&
		    !ipv4_is_multicast(spec->loc_host[0]))
			return true;
		if (spec->ether_type == htons(ETH_P_IPV6) &&
		    ((const u8 *)spec->loc_host)[0] != 0xff)
			return true;
	}

	return false;
}