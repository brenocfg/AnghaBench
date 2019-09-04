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
struct p54_common {int /*<<< orphan*/ * survey; int /*<<< orphan*/ * used_rxkeys; int /*<<< orphan*/ * rssi_db; int /*<<< orphan*/ * curve_data; int /*<<< orphan*/ * output_limit; int /*<<< orphan*/ * iq_autocal; int /*<<< orphan*/ ** band_table; } ;
struct ieee80211_hw {struct p54_common* priv; } ;

/* Variables and functions */
 unsigned int NUM_NL80211_BANDS ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void p54_free_common(struct ieee80211_hw *dev)
{
	struct p54_common *priv = dev->priv;
	unsigned int i;

	for (i = 0; i < NUM_NL80211_BANDS; i++)
		kfree(priv->band_table[i]);

	kfree(priv->iq_autocal);
	kfree(priv->output_limit);
	kfree(priv->curve_data);
	kfree(priv->rssi_db);
	kfree(priv->used_rxkeys);
	kfree(priv->survey);
	priv->iq_autocal = NULL;
	priv->output_limit = NULL;
	priv->curve_data = NULL;
	priv->rssi_db = NULL;
	priv->used_rxkeys = NULL;
	priv->survey = NULL;
	ieee80211_free_hw(dev);
}