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
typedef  int u8 ;
typedef  int u16 ;
struct rtl8187_priv {int* aifsn; int slot_time; TYPE_1__* map; scalar_t__ is_rtl8187b; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_queue_params {int aifs; int txop; int /*<<< orphan*/  cw_max; int /*<<< orphan*/  cw_min; } ;
struct ieee80211_hw {struct rtl8187_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  CW_VAL; } ;

/* Variables and functions */
 int EINVAL ; 
 int SIFS_TIME ; 
 int fls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rtl8187b_ac_addr ; 
 int /*<<< orphan*/  rtl818x_iowrite32 (struct rtl8187_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8187_priv*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rtl8187_conf_tx(struct ieee80211_hw *dev,
			   struct ieee80211_vif *vif, u16 queue,
			   const struct ieee80211_tx_queue_params *params)
{
	struct rtl8187_priv *priv = dev->priv;
	u8 cw_min, cw_max;

	if (queue > 3)
		return -EINVAL;

	cw_min = fls(params->cw_min);
	cw_max = fls(params->cw_max);

	if (priv->is_rtl8187b) {
		priv->aifsn[queue] = params->aifs;

		/*
		 * This is the structure of AC_*_PARAM registers in 8187B:
		 * - TXOP limit field, bit offset = 16
		 * - ECWmax, bit offset = 12
		 * - ECWmin, bit offset = 8
		 * - AIFS, bit offset = 0
		 */
		rtl818x_iowrite32(priv, rtl8187b_ac_addr[queue],
				  (params->txop << 16) | (cw_max << 12) |
				  (cw_min << 8) | (params->aifs *
				  priv->slot_time + SIFS_TIME));
	} else {
		if (queue != 0)
			return -EINVAL;

		rtl818x_iowrite8(priv, &priv->map->CW_VAL,
				 cw_min | (cw_max << 4));
	}
	return 0;
}