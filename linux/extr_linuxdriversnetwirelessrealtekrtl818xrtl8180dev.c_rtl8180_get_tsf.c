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
typedef  int u64 ;
struct rtl8180_priv {TYPE_1__* map; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/ * TSFT; } ;

/* Variables and functions */
 int rtl818x_ioread32 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 rtl8180_get_tsf(struct ieee80211_hw *dev,
			   struct ieee80211_vif *vif)
{
	struct rtl8180_priv *priv = dev->priv;

	return rtl818x_ioread32(priv, &priv->map->TSFT[0]) |
	       (u64)(rtl818x_ioread32(priv, &priv->map->TSFT[1])) << 32;
}