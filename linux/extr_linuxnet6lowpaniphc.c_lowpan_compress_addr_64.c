#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct net_device {int dummy; } ;
struct in6_addr {int /*<<< orphan*/ * s6_addr16; } ;
struct TYPE_2__ {int lltype; } ;

/* Variables and functions */
 size_t LOWPAN_IPHC_DAM_01 ; 
 size_t LOWPAN_IPHC_DAM_10 ; 
 size_t LOWPAN_IPHC_DAM_11 ; 
#define  LOWPAN_LLTYPE_IEEE802154 128 
 TYPE_1__* lowpan_dev (struct net_device const*) ; 
 int /*<<< orphan*/  lowpan_iphc_addr_equal (struct net_device const*,int /*<<< orphan*/ *,struct in6_addr const*,unsigned char const*) ; 
 int /*<<< orphan*/  lowpan_iphc_compress_802154_lladdr (struct in6_addr const*,unsigned char const*) ; 
 size_t* lowpan_iphc_dam_to_sam_value ; 
 scalar_t__ lowpan_is_iid_16_bit_compressable (struct in6_addr const*) ; 
 int /*<<< orphan*/  lowpan_push_hc_data (size_t**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  raw_dump_inline (int /*<<< orphan*/ *,char*,size_t*,int) ; 

__attribute__((used)) static u8 lowpan_compress_addr_64(u8 **hc_ptr, const struct net_device *dev,
				  const struct in6_addr *ipaddr,
				  const unsigned char *lladdr, bool sam)
{
	u8 dam = LOWPAN_IPHC_DAM_01;

	switch (lowpan_dev(dev)->lltype) {
	case LOWPAN_LLTYPE_IEEE802154:
		if (lowpan_iphc_compress_802154_lladdr(ipaddr, lladdr)) {
			dam = LOWPAN_IPHC_DAM_11; /* 0-bits */
			pr_debug("address compression 0 bits\n");
			goto out;
		}
		break;
	default:
		if (lowpan_iphc_addr_equal(dev, NULL, ipaddr, lladdr)) {
			dam = LOWPAN_IPHC_DAM_11;
			pr_debug("address compression 0 bits\n");
			goto out;
		}

		break;
	}

	if (lowpan_is_iid_16_bit_compressable(ipaddr)) {
		/* compress IID to 16 bits xxxx::XXXX */
		lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr16[7], 2);
		dam = LOWPAN_IPHC_DAM_10; /* 16-bits */
		raw_dump_inline(NULL, "Compressed ipv6 addr is (16 bits)",
				*hc_ptr - 2, 2);
		goto out;
	}

	/* do not compress IID => xxxx::IID */
	lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr16[4], 8);
	raw_dump_inline(NULL, "Compressed ipv6 addr is (64 bits)",
			*hc_ptr - 8, 8);

out:

	if (sam)
		return lowpan_iphc_dam_to_sam_value[dam];
	else
		return dam;
}