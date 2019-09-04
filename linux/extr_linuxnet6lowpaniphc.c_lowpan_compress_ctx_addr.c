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
typedef  int /*<<< orphan*/  tmp ;
struct net_device {int dummy; } ;
struct lowpan_iphc_ctx {int /*<<< orphan*/  plen; int /*<<< orphan*/  pfx; } ;
struct in6_addr {int* s6_addr; } ;
struct TYPE_2__ {int lltype; } ;

/* Variables and functions */
 size_t LOWPAN_IPHC_DAM_00 ; 
 size_t LOWPAN_IPHC_DAM_01 ; 
 size_t LOWPAN_IPHC_DAM_10 ; 
 size_t LOWPAN_IPHC_DAM_11 ; 
#define  LOWPAN_LLTYPE_IEEE802154 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 scalar_t__ ipv6_addr_equal (struct in6_addr*,struct in6_addr const*) ; 
 int /*<<< orphan*/  ipv6_addr_prefix_copy (struct in6_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* lowpan_dev (struct net_device const*) ; 
 int /*<<< orphan*/  lowpan_iphc_addr_equal (struct net_device const*,struct lowpan_iphc_ctx const*,struct in6_addr const*,unsigned char const*) ; 
 int /*<<< orphan*/  lowpan_iphc_compress_ctx_802154_lladdr (struct in6_addr const*,struct lowpan_iphc_ctx const*,unsigned char const*) ; 
 size_t* lowpan_iphc_dam_to_sam_value ; 
 int /*<<< orphan*/  lowpan_push_hc_data (size_t**,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (struct in6_addr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 lowpan_compress_ctx_addr(u8 **hc_ptr, const struct net_device *dev,
				   const struct in6_addr *ipaddr,
				   const struct lowpan_iphc_ctx *ctx,
				   const unsigned char *lladdr, bool sam)
{
	struct in6_addr tmp = {};
	u8 dam;

	switch (lowpan_dev(dev)->lltype) {
	case LOWPAN_LLTYPE_IEEE802154:
		if (lowpan_iphc_compress_ctx_802154_lladdr(ipaddr, ctx,
							   lladdr)) {
			dam = LOWPAN_IPHC_DAM_11;
			goto out;
		}
		break;
	default:
		if (lowpan_iphc_addr_equal(dev, ctx, ipaddr, lladdr)) {
			dam = LOWPAN_IPHC_DAM_11;
			goto out;
		}
		break;
	}

	memset(&tmp, 0, sizeof(tmp));
	/* check for SAM/DAM = 10 */
	tmp.s6_addr[11] = 0xFF;
	tmp.s6_addr[12] = 0xFE;
	memcpy(&tmp.s6_addr[14], &ipaddr->s6_addr[14], 2);
	/* context information are always used */
	ipv6_addr_prefix_copy(&tmp, &ctx->pfx, ctx->plen);
	if (ipv6_addr_equal(&tmp, ipaddr)) {
		lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr[14], 2);
		dam = LOWPAN_IPHC_DAM_10;
		goto out;
	}

	memset(&tmp, 0, sizeof(tmp));
	/* check for SAM/DAM = 01, should always match */
	memcpy(&tmp.s6_addr[8], &ipaddr->s6_addr[8], 8);
	/* context information are always used */
	ipv6_addr_prefix_copy(&tmp, &ctx->pfx, ctx->plen);
	if (ipv6_addr_equal(&tmp, ipaddr)) {
		lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr[8], 8);
		dam = LOWPAN_IPHC_DAM_01;
		goto out;
	}

	WARN_ONCE(1, "context found but no address mode matched\n");
	return LOWPAN_IPHC_DAM_00;
out:

	if (sam)
		return lowpan_iphc_dam_to_sam_value[dam];
	else
		return dam;
}