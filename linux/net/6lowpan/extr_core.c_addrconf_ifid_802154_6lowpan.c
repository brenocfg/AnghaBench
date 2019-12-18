#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct wpan_dev {scalar_t__ short_addr; scalar_t__ pan_id; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* wdev; } ;
struct TYPE_3__ {struct wpan_dev* ieee802154_ptr; } ;

/* Variables and functions */
 int IEEE802154_PAN_ID_BROADCAST ; 
 scalar_t__ cpu_to_le16 (int) ; 
 int /*<<< orphan*/  ieee802154_le16_to_be16 (int*,scalar_t__*) ; 
 TYPE_2__* lowpan_802154_dev (struct net_device*) ; 
 int /*<<< orphan*/  lowpan_802154_is_valid_src_short_addr (scalar_t__) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

int addrconf_ifid_802154_6lowpan(u8 *eui, struct net_device *dev)
{
	struct wpan_dev *wpan_dev = lowpan_802154_dev(dev)->wdev->ieee802154_ptr;

	/* Set short_addr autoconfiguration if short_addr is present only */
	if (!lowpan_802154_is_valid_src_short_addr(wpan_dev->short_addr))
		return -1;

	/* For either address format, all zero addresses MUST NOT be used */
	if (wpan_dev->pan_id == cpu_to_le16(0x0000) &&
	    wpan_dev->short_addr == cpu_to_le16(0x0000))
		return -1;

	/* Alternatively, if no PAN ID is known, 16 zero bits may be used */
	if (wpan_dev->pan_id == cpu_to_le16(IEEE802154_PAN_ID_BROADCAST))
		memset(eui, 0, 2);
	else
		ieee802154_le16_to_be16(eui, &wpan_dev->pan_id);

	/* The "Universal/Local" (U/L) bit shall be set to zero */
	eui[0] &= ~2;
	eui[2] = 0;
	eui[3] = 0xFF;
	eui[4] = 0xFE;
	eui[5] = 0;
	ieee802154_le16_to_be16(&eui[6], &wpan_dev->short_addr);
	return 0;
}