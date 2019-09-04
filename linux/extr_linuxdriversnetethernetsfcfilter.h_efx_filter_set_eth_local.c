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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct efx_filter_spec {int /*<<< orphan*/  loc_mac; int /*<<< orphan*/  match_flags; int /*<<< orphan*/  outer_vid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_FILTER_MATCH_LOC_MAC ; 
 int /*<<< orphan*/  EFX_FILTER_MATCH_OUTER_VID ; 
 scalar_t__ EFX_FILTER_VID_UNSPEC ; 
 int EINVAL ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 

__attribute__((used)) static inline int efx_filter_set_eth_local(struct efx_filter_spec *spec,
					   u16 vid, const u8 *addr)
{
	if (vid == EFX_FILTER_VID_UNSPEC && addr == NULL)
		return -EINVAL;

	if (vid != EFX_FILTER_VID_UNSPEC) {
		spec->match_flags |= EFX_FILTER_MATCH_OUTER_VID;
		spec->outer_vid = htons(vid);
	}
	if (addr != NULL) {
		spec->match_flags |= EFX_FILTER_MATCH_LOC_MAC;
		ether_addr_copy(spec->loc_mac, addr);
	}
	return 0;
}