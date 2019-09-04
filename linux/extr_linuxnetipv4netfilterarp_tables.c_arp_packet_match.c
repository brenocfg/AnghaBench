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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int /*<<< orphan*/  addr_len; } ;
struct TYPE_8__ {int s_addr; } ;
struct TYPE_7__ {int s_addr; } ;
struct TYPE_6__ {int s_addr; } ;
struct TYPE_5__ {int s_addr; } ;
struct arpt_arp {int arpop_mask; int arpop; int arhrd_mask; int arhrd; int arpro_mask; int arpro; int arhln_mask; int arhln; int /*<<< orphan*/  outiface_mask; int /*<<< orphan*/  outiface; int /*<<< orphan*/  iniface_mask; int /*<<< orphan*/  iniface; TYPE_4__ tgt; TYPE_3__ tmsk; TYPE_2__ src; TYPE_1__ smsk; int /*<<< orphan*/  tgt_devaddr; int /*<<< orphan*/  src_devaddr; } ;
struct arphdr {int ar_op; int ar_hrd; int ar_pro; int ar_hln; } ;
typedef  int __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARPT_INV_ARPHLN ; 
 int /*<<< orphan*/  ARPT_INV_ARPHRD ; 
 int /*<<< orphan*/  ARPT_INV_ARPOP ; 
 int /*<<< orphan*/  ARPT_INV_ARPPRO ; 
 int /*<<< orphan*/  ARPT_INV_SRCDEVADDR ; 
 int /*<<< orphan*/  ARPT_INV_SRCIP ; 
 int /*<<< orphan*/  ARPT_INV_TGTDEVADDR ; 
 int /*<<< orphan*/  ARPT_INV_TGTIP ; 
 int /*<<< orphan*/  ARPT_INV_VIA_IN ; 
 int /*<<< orphan*/  ARPT_INV_VIA_OUT ; 
 scalar_t__ NF_INVF (struct arpt_arp const*,int /*<<< orphan*/ ,int) ; 
 int arp_devaddr_compare (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 long ifname_compare (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,char const*,int) ; 

__attribute__((used)) static inline int arp_packet_match(const struct arphdr *arphdr,
				   struct net_device *dev,
				   const char *indev,
				   const char *outdev,
				   const struct arpt_arp *arpinfo)
{
	const char *arpptr = (char *)(arphdr + 1);
	const char *src_devaddr, *tgt_devaddr;
	__be32 src_ipaddr, tgt_ipaddr;
	long ret;

	if (NF_INVF(arpinfo, ARPT_INV_ARPOP,
		    (arphdr->ar_op & arpinfo->arpop_mask) != arpinfo->arpop))
		return 0;

	if (NF_INVF(arpinfo, ARPT_INV_ARPHRD,
		    (arphdr->ar_hrd & arpinfo->arhrd_mask) != arpinfo->arhrd))
		return 0;

	if (NF_INVF(arpinfo, ARPT_INV_ARPPRO,
		    (arphdr->ar_pro & arpinfo->arpro_mask) != arpinfo->arpro))
		return 0;

	if (NF_INVF(arpinfo, ARPT_INV_ARPHLN,
		    (arphdr->ar_hln & arpinfo->arhln_mask) != arpinfo->arhln))
		return 0;

	src_devaddr = arpptr;
	arpptr += dev->addr_len;
	memcpy(&src_ipaddr, arpptr, sizeof(u32));
	arpptr += sizeof(u32);
	tgt_devaddr = arpptr;
	arpptr += dev->addr_len;
	memcpy(&tgt_ipaddr, arpptr, sizeof(u32));

	if (NF_INVF(arpinfo, ARPT_INV_SRCDEVADDR,
		    arp_devaddr_compare(&arpinfo->src_devaddr, src_devaddr,
					dev->addr_len)) ||
	    NF_INVF(arpinfo, ARPT_INV_TGTDEVADDR,
		    arp_devaddr_compare(&arpinfo->tgt_devaddr, tgt_devaddr,
					dev->addr_len)))
		return 0;

	if (NF_INVF(arpinfo, ARPT_INV_SRCIP,
		    (src_ipaddr & arpinfo->smsk.s_addr) != arpinfo->src.s_addr) ||
	    NF_INVF(arpinfo, ARPT_INV_TGTIP,
		    (tgt_ipaddr & arpinfo->tmsk.s_addr) != arpinfo->tgt.s_addr))
		return 0;

	/* Look for ifname matches.  */
	ret = ifname_compare(indev, arpinfo->iniface, arpinfo->iniface_mask);

	if (NF_INVF(arpinfo, ARPT_INV_VIA_IN, ret != 0))
		return 0;

	ret = ifname_compare(outdev, arpinfo->outiface, arpinfo->outiface_mask);

	if (NF_INVF(arpinfo, ARPT_INV_VIA_OUT, ret != 0))
		return 0;

	return 1;
}