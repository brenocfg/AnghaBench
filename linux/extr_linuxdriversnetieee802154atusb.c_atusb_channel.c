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
struct ieee802154_hw {struct atusb* priv; } ;
struct atusb {TYPE_1__* data; } ;
struct TYPE_2__ {int (* set_channel ) (struct ieee802154_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  t_channel_switch; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int stub1 (struct ieee802154_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atusb_channel(struct ieee802154_hw *hw, u8 page, u8 channel)
{
	struct atusb *atusb = hw->priv;
	int ret = -ENOTSUPP;

	if (atusb->data) {
		ret = atusb->data->set_channel(hw, page, channel);
		/* @@@ ugly synchronization */
		msleep(atusb->data->t_channel_switch);
	}

	return ret;
}