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
struct lowpan_iphc_ctx {int /*<<< orphan*/  plen; int /*<<< orphan*/  pfx; } ;
struct in6_addr {int* s6_addr; int /*<<< orphan*/ * s6_addr16; } ;
struct ieee802154_addr {int mode; int /*<<< orphan*/  short_addr; int /*<<< orphan*/  extended_addr; } ;

/* Variables and functions */
 int EUI64_ADDR_LEN ; 
#define  IEEE802154_ADDR_LONG 129 
#define  IEEE802154_ADDR_SHORT 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ieee802154_le16_to_be16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee802154_le64_to_be64 (unsigned char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_addr_equal (struct in6_addr*,struct in6_addr const*) ; 
 int /*<<< orphan*/  ipv6_addr_prefix_copy (struct in6_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,unsigned char**,int) ; 

__attribute__((used)) static inline bool
lowpan_iphc_compress_ctx_802154_lladdr(const struct in6_addr *ipaddr,
				       const struct lowpan_iphc_ctx *ctx,
				       const void *lladdr)
{
	const struct ieee802154_addr *addr = lladdr;
	unsigned char extended_addr[EUI64_ADDR_LEN];
	bool lladdr_compress = false;
	struct in6_addr tmp = {};

	switch (addr->mode) {
	case IEEE802154_ADDR_LONG:
		ieee802154_le64_to_be64(&extended_addr, &addr->extended_addr);
		/* check for SAM/DAM = 11 */
		memcpy(&tmp.s6_addr[8], &extended_addr, EUI64_ADDR_LEN);
		/* second bit-flip (Universe/Local) is done according RFC2464 */
		tmp.s6_addr[8] ^= 0x02;
		/* context information are always used */
		ipv6_addr_prefix_copy(&tmp, &ctx->pfx, ctx->plen);
		if (ipv6_addr_equal(&tmp, ipaddr))
			lladdr_compress = true;
		break;
	case IEEE802154_ADDR_SHORT:
		tmp.s6_addr[11] = 0xFF;
		tmp.s6_addr[12] = 0xFE;
		ieee802154_le16_to_be16(&tmp.s6_addr16[7],
					&addr->short_addr);
		/* context information are always used */
		ipv6_addr_prefix_copy(&tmp, &ctx->pfx, ctx->plen);
		if (ipv6_addr_equal(&tmp, ipaddr))
			lladdr_compress = true;
		break;
	default:
		/* should never handled and filtered by 802154 6lowpan */
		WARN_ON_ONCE(1);
		break;
	}

	return lladdr_compress;
}