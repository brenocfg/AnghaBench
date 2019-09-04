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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int /*<<< orphan*/  dev_addr; TYPE_1__* ieee802154_ptr; } ;
struct ieee802154_llsec_params {int /*<<< orphan*/  coord_shortaddr; int /*<<< orphan*/  hwaddr; int /*<<< orphan*/  coord_hwaddr; int /*<<< orphan*/  pan_id; } ;
struct ieee802154_addr {scalar_t__ mode; int /*<<< orphan*/  short_addr; int /*<<< orphan*/  pan_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  short_addr; int /*<<< orphan*/  pan_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IEEE802154_ADDR_SHORT ; 
 int IEEE802154_LLSEC_PARAM_COORD_HWADDR ; 
 int IEEE802154_LLSEC_PARAM_COORD_SHORTADDR ; 
 int IEEE802154_LLSEC_PARAM_HWADDR ; 
 int IEEE802154_LLSEC_PARAM_PAN_ID ; 
 int /*<<< orphan*/  ieee802154_devaddr_from_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac802154_dev_set_page_channel (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mac802154_set_params (struct net_device*,struct ieee802154_llsec_params*,int) ; 

__attribute__((used)) static int mac802154_mlme_start_req(struct net_device *dev,
				    struct ieee802154_addr *addr,
				    u8 channel, u8 page,
				    u8 bcn_ord, u8 sf_ord,
				    u8 pan_coord, u8 blx,
				    u8 coord_realign)
{
	struct ieee802154_llsec_params params;
	int changed = 0;

	ASSERT_RTNL();

	BUG_ON(addr->mode != IEEE802154_ADDR_SHORT);

	dev->ieee802154_ptr->pan_id = addr->pan_id;
	dev->ieee802154_ptr->short_addr = addr->short_addr;
	mac802154_dev_set_page_channel(dev, page, channel);

	params.pan_id = addr->pan_id;
	changed |= IEEE802154_LLSEC_PARAM_PAN_ID;

	params.hwaddr = ieee802154_devaddr_from_raw(dev->dev_addr);
	changed |= IEEE802154_LLSEC_PARAM_HWADDR;

	params.coord_hwaddr = params.hwaddr;
	changed |= IEEE802154_LLSEC_PARAM_COORD_HWADDR;

	params.coord_shortaddr = addr->short_addr;
	changed |= IEEE802154_LLSEC_PARAM_COORD_SHORTADDR;

	return mac802154_set_params(dev, &params, changed);
}