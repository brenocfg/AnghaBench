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
typedef  scalar_t__ u8 ;
struct mrf24j40 {int /*<<< orphan*/  regmap_short; int /*<<< orphan*/  regmap_long; } ;
struct ieee802154_hw {struct mrf24j40* priv; } ;

/* Variables and functions */
 scalar_t__ BIT_RFRST ; 
 scalar_t__ MRF24J40_CHAN_MAX ; 
 scalar_t__ MRF24J40_CHAN_MIN ; 
 int /*<<< orphan*/  REG_RFCON0 ; 
 int /*<<< orphan*/  REG_RFCTL ; 
 scalar_t__ RFCON0_CH_MASK ; 
 scalar_t__ RFCON0_CH_SHIFT ; 
 scalar_t__ RFOPT_RECOMMEND ; 
 int /*<<< orphan*/  SET_CHANNEL_DELAY_US ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  printdev (struct mrf24j40*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mrf24j40_set_channel(struct ieee802154_hw *hw, u8 page, u8 channel)
{
	struct mrf24j40 *devrec = hw->priv;
	u8 val;
	int ret;

	dev_dbg(printdev(devrec), "Set Channel %d\n", channel);

	WARN_ON(page != 0);
	WARN_ON(channel < MRF24J40_CHAN_MIN);
	WARN_ON(channel > MRF24J40_CHAN_MAX);

	/* Set Channel TODO */
	val = (channel - 11) << RFCON0_CH_SHIFT | RFOPT_RECOMMEND;
	ret = regmap_update_bits(devrec->regmap_long, REG_RFCON0,
				 RFCON0_CH_MASK, val);
	if (ret)
		return ret;

	/* RF Reset */
	ret = regmap_update_bits(devrec->regmap_short, REG_RFCTL, BIT_RFRST,
				 BIT_RFRST);
	if (ret)
		return ret;

	ret = regmap_update_bits(devrec->regmap_short, REG_RFCTL, BIT_RFRST, 0);
	if (!ret)
		udelay(SET_CHANNEL_DELAY_US); /* per datasheet */

	return ret;
}