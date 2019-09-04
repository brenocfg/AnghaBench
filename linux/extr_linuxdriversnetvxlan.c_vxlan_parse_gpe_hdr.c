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
typedef  int /*<<< orphan*/  u32 ;
struct vxlanhdr_gpe {scalar_t__ version; int /*<<< orphan*/  next_protocol; scalar_t__ oam_flag; int /*<<< orphan*/  np_applied; } ;
struct vxlanhdr {int /*<<< orphan*/  vx_flags; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  VXLAN_GPE_USED_BITS ; 
 int /*<<< orphan*/  tun_p_to_eth_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vxlan_parse_gpe_hdr(struct vxlanhdr *unparsed,
				__be16 *protocol,
				struct sk_buff *skb, u32 vxflags)
{
	struct vxlanhdr_gpe *gpe = (struct vxlanhdr_gpe *)unparsed;

	/* Need to have Next Protocol set for interfaces in GPE mode. */
	if (!gpe->np_applied)
		return false;
	/* "The initial version is 0. If a receiver does not support the
	 * version indicated it MUST drop the packet.
	 */
	if (gpe->version != 0)
		return false;
	/* "When the O bit is set to 1, the packet is an OAM packet and OAM
	 * processing MUST occur." However, we don't implement OAM
	 * processing, thus drop the packet.
	 */
	if (gpe->oam_flag)
		return false;

	*protocol = tun_p_to_eth_p(gpe->next_protocol);
	if (!*protocol)
		return false;

	unparsed->vx_flags &= ~VXLAN_GPE_USED_BITS;
	return true;
}