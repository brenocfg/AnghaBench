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
struct rtl8187_priv {int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/ * vif; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct rtl8187_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl8187_remove_interface(struct ieee80211_hw *dev,
				     struct ieee80211_vif *vif)
{
	struct rtl8187_priv *priv = dev->priv;
	mutex_lock(&priv->conf_mutex);
	priv->vif = NULL;
	mutex_unlock(&priv->conf_mutex);
}