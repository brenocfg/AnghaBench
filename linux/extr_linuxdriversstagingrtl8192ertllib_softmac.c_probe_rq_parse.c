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
typedef  scalar_t__ u8 ;
struct sk_buff {int len; scalar_t__* data; } ;
struct rtllib_hdr_3addr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr3; } ;
struct TYPE_2__ {int /*<<< orphan*/  ssid; int /*<<< orphan*/  bssid; } ;
struct rtllib_device {TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static short probe_rq_parse(struct rtllib_device *ieee, struct sk_buff *skb,
			    u8 *src)
{
	u8 *tag;
	u8 *skbend;
	u8 *ssid = NULL;
	u8 ssidlen = 0;
	struct rtllib_hdr_3addr   *header =
		(struct rtllib_hdr_3addr   *) skb->data;
	bool bssid_match;

	if (skb->len < sizeof(struct rtllib_hdr_3addr))
		return -1; /* corrupted */

	bssid_match =
	  (!ether_addr_equal(header->addr3, ieee->current_network.bssid)) &&
	  (!is_broadcast_ether_addr(header->addr3));
	if (bssid_match)
		return -1;

	ether_addr_copy(src, header->addr2);

	skbend = (u8 *)skb->data + skb->len;

	tag = skb->data + sizeof(struct rtllib_hdr_3addr);

	while (tag + 1 < skbend) {
		if (*tag == 0) {
			ssid = tag + 2;
			ssidlen = *(tag + 1);
			break;
		}
		tag++; /* point to the len field */
		tag = tag + *(tag); /* point to the last data byte of the tag */
		tag++; /* point to the next tag */
	}

	if (ssidlen == 0)
		return 1;

	if (!ssid)
		return 1; /* ssid not found in tagged param */

	return !strncmp(ssid, ieee->current_network.ssid, ssidlen);
}