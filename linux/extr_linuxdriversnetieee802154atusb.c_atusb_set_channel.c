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
struct ieee802154_hw {struct atusb* priv; } ;
struct atusb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SR_CHANNEL ; 
 int atusb_write_subreg (struct atusb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atusb_set_channel(struct ieee802154_hw *hw, u8 page, u8 channel)
{
	struct atusb *atusb = hw->priv;
	int ret;

	ret = atusb_write_subreg(atusb, SR_CHANNEL, channel);
	if (ret < 0)
		return ret;
	return 0;
}