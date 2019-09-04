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
struct in6_addr {int* s6_addr; int /*<<< orphan*/ * s6_addr16; } ;
struct ieee802154_addr {int mode; int /*<<< orphan*/  short_addr; int /*<<< orphan*/  extended_addr; } ;

/* Variables and functions */
 int EUI64_ADDR_LEN ; 
#define  IEEE802154_ADDR_LONG 129 
#define  IEEE802154_ADDR_SHORT 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ieee802154_le16_to_be16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee802154_le64_to_be64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lowpan_iphc_uncompress_eui64_lladdr (struct in6_addr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
lowpan_iphc_uncompress_802154_lladdr(struct in6_addr *ipaddr,
				     const void *lladdr)
{
	const struct ieee802154_addr *addr = lladdr;
	u8 eui64[EUI64_ADDR_LEN];

	switch (addr->mode) {
	case IEEE802154_ADDR_LONG:
		ieee802154_le64_to_be64(eui64, &addr->extended_addr);
		lowpan_iphc_uncompress_eui64_lladdr(ipaddr, eui64);
		break;
	case IEEE802154_ADDR_SHORT:
		/* fe:80::ff:fe00:XXXX
		 *                \__/
		 *             short_addr
		 *
		 * Universe/Local bit is zero.
		 */
		ipaddr->s6_addr[0] = 0xFE;
		ipaddr->s6_addr[1] = 0x80;
		ipaddr->s6_addr[11] = 0xFF;
		ipaddr->s6_addr[12] = 0xFE;
		ieee802154_le16_to_be16(&ipaddr->s6_addr16[7],
					&addr->short_addr);
		break;
	default:
		/* should never handled and filtered by 802154 6lowpan */
		WARN_ON_ONCE(1);
		break;
	}
}