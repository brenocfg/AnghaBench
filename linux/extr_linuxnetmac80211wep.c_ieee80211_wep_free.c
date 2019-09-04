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
struct ieee80211_local {int /*<<< orphan*/  wep_rx_tfm; int /*<<< orphan*/  wep_tx_tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_cipher (int /*<<< orphan*/ ) ; 

void ieee80211_wep_free(struct ieee80211_local *local)
{
	if (!IS_ERR(local->wep_tx_tfm))
		crypto_free_cipher(local->wep_tx_tfm);
	if (!IS_ERR(local->wep_rx_tfm))
		crypto_free_cipher(local->wep_rx_tfm);
}