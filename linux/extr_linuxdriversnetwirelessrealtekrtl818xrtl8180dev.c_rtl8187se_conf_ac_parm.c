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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct rtl8180_priv {int slot_time; TYPE_1__* map; struct ieee80211_tx_queue_params* queue_param; } ;
struct ieee80211_tx_queue_params {int aifs; size_t txop; int /*<<< orphan*/  cw_max; int /*<<< orphan*/  cw_min; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  AC_VO_PARAM; int /*<<< orphan*/  AC_VI_PARAM; int /*<<< orphan*/  AC_BE_PARAM; int /*<<< orphan*/  AC_BK_PARAM; } ;

/* Variables and functions */
 size_t AC_PARAM_AIFS_SHIFT ; 
 size_t AC_PARAM_ECW_MAX_SHIFT ; 
 size_t AC_PARAM_ECW_MIN_SHIFT ; 
 size_t AC_PARAM_TXOP_LIMIT_SHIFT ; 
#define  IEEE80211_AC_BE 131 
#define  IEEE80211_AC_BK 130 
#define  IEEE80211_AC_VI 129 
#define  IEEE80211_AC_VO 128 
 size_t fls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl818x_iowrite32 (struct rtl8180_priv*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void rtl8187se_conf_ac_parm(struct ieee80211_hw *dev, u8 queue)
{
	const struct ieee80211_tx_queue_params *params;
	struct rtl8180_priv *priv = dev->priv;

	/* hw value */
	u32 ac_param;

	u8 aifs;
	u8 txop;
	u8 cw_min, cw_max;

	params = &priv->queue_param[queue];

	cw_min = fls(params->cw_min);
	cw_max = fls(params->cw_max);

	aifs = 10 + params->aifs * priv->slot_time;

	/* TODO: check if txop HW is in us (mult by 32) */
	txop = params->txop;

	ac_param = txop << AC_PARAM_TXOP_LIMIT_SHIFT |
		cw_max << AC_PARAM_ECW_MAX_SHIFT |
		cw_min << AC_PARAM_ECW_MIN_SHIFT |
		aifs << AC_PARAM_AIFS_SHIFT;

	switch (queue) {
	case IEEE80211_AC_BK:
		rtl818x_iowrite32(priv, &priv->map->AC_BK_PARAM, ac_param);
		break;
	case IEEE80211_AC_BE:
		rtl818x_iowrite32(priv, &priv->map->AC_BE_PARAM, ac_param);
		break;
	case IEEE80211_AC_VI:
		rtl818x_iowrite32(priv, &priv->map->AC_VI_PARAM, ac_param);
		break;
	case IEEE80211_AC_VO:
		rtl818x_iowrite32(priv, &priv->map->AC_VO_PARAM, ac_param);
		break;
	}
}