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
struct ieee802154_hw {struct at86rf230_local* priv; } ;
struct at86rf230_local {scalar_t__ cal_timeout; TYPE_1__* data; } ;
struct TYPE_2__ {int (* set_channel ) (struct at86rf230_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ t_channel_switch; } ;

/* Variables and functions */
 scalar_t__ AT86RF2XX_CAL_LOOP_TIMEOUT ; 
 scalar_t__ jiffies ; 
 int stub1 (struct at86rf230_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
at86rf230_channel(struct ieee802154_hw *hw, u8 page, u8 channel)
{
	struct at86rf230_local *lp = hw->priv;
	int rc;

	rc = lp->data->set_channel(lp, page, channel);
	/* Wait for PLL */
	usleep_range(lp->data->t_channel_switch,
		     lp->data->t_channel_switch + 10);

	lp->cal_timeout = jiffies + AT86RF2XX_CAL_LOOP_TIMEOUT;
	return rc;
}