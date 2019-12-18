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
struct lib80211_tkip_data {int /*<<< orphan*/  rx_tfm_michael; int /*<<< orphan*/  tx_tfm_michael; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (void*) ; 

__attribute__((used)) static void lib80211_tkip_deinit(void *priv)
{
	struct lib80211_tkip_data *_priv = priv;
	if (_priv) {
		crypto_free_shash(_priv->tx_tfm_michael);
		crypto_free_shash(_priv->rx_tfm_michael);
	}
	kzfree(priv);
}