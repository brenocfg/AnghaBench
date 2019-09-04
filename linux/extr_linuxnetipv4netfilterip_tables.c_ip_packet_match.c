#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int s_addr; } ;
struct TYPE_7__ {int s_addr; } ;
struct TYPE_6__ {int s_addr; } ;
struct TYPE_5__ {int s_addr; } ;
struct ipt_ip {scalar_t__ proto; int flags; int /*<<< orphan*/  outiface_mask; int /*<<< orphan*/  outiface; int /*<<< orphan*/  iniface_mask; int /*<<< orphan*/  iniface; TYPE_4__ dst; TYPE_3__ dmsk; TYPE_2__ src; TYPE_1__ smsk; } ;
struct iphdr {int saddr; int daddr; scalar_t__ protocol; } ;

/* Variables and functions */
 int IPT_F_FRAG ; 
 int /*<<< orphan*/  IPT_INV_DSTIP ; 
 int /*<<< orphan*/  IPT_INV_FRAG ; 
 int /*<<< orphan*/  IPT_INV_PROTO ; 
 int /*<<< orphan*/  IPT_INV_SRCIP ; 
 int /*<<< orphan*/  IPT_INV_VIA_IN ; 
 int /*<<< orphan*/  IPT_INV_VIA_OUT ; 
 scalar_t__ NF_INVF (struct ipt_ip const*,int /*<<< orphan*/ ,int) ; 
 unsigned long ifname_compare_aligned (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
ip_packet_match(const struct iphdr *ip,
		const char *indev,
		const char *outdev,
		const struct ipt_ip *ipinfo,
		int isfrag)
{
	unsigned long ret;

	if (NF_INVF(ipinfo, IPT_INV_SRCIP,
		    (ip->saddr & ipinfo->smsk.s_addr) != ipinfo->src.s_addr) ||
	    NF_INVF(ipinfo, IPT_INV_DSTIP,
		    (ip->daddr & ipinfo->dmsk.s_addr) != ipinfo->dst.s_addr))
		return false;

	ret = ifname_compare_aligned(indev, ipinfo->iniface, ipinfo->iniface_mask);

	if (NF_INVF(ipinfo, IPT_INV_VIA_IN, ret != 0))
		return false;

	ret = ifname_compare_aligned(outdev, ipinfo->outiface, ipinfo->outiface_mask);

	if (NF_INVF(ipinfo, IPT_INV_VIA_OUT, ret != 0))
		return false;

	/* Check specific protocol */
	if (ipinfo->proto &&
	    NF_INVF(ipinfo, IPT_INV_PROTO, ip->protocol != ipinfo->proto))
		return false;

	/* If we have a fragment rule but the packet is not a fragment
	 * then we return zero */
	if (NF_INVF(ipinfo, IPT_INV_FRAG,
		    (ipinfo->flags & IPT_F_FRAG) && !isfrag))
		return false;

	return true;
}