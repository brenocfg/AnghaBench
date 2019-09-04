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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ mode; int /*<<< orphan*/  extended_addr; } ;
struct ieee802154_hdr {TYPE_1__ source; } ;

/* Variables and functions */
 scalar_t__ IEEE802154_ADDR_LONG ; 
 int IEEE802154_EXTENDED_ADDR_LEN ; 
 scalar_t__ ieee802154_hdr_peek_addrs (struct sk_buff const*,struct ieee802154_hdr*) ; 
 int /*<<< orphan*/  ieee802154_le64_to_be64 (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int
mac802154_header_parse(const struct sk_buff *skb, unsigned char *haddr)
{
	struct ieee802154_hdr hdr;

	if (ieee802154_hdr_peek_addrs(skb, &hdr) < 0) {
		pr_debug("malformed packet\n");
		return 0;
	}

	if (hdr.source.mode == IEEE802154_ADDR_LONG) {
		ieee802154_le64_to_be64(haddr, &hdr.source.extended_addr);
		return IEEE802154_EXTENDED_ADDR_LEN;
	}

	return 0;
}