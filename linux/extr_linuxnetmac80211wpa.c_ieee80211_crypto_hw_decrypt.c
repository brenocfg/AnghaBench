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
struct ieee80211_rx_data {TYPE_1__* sta; } ;
typedef  int /*<<< orphan*/  ieee80211_rx_result ;
struct TYPE_2__ {scalar_t__ cipher_scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_DROP_UNUSABLE ; 
 int /*<<< orphan*/  ieee80211_crypto_cs_decrypt (struct ieee80211_rx_data*) ; 

ieee80211_rx_result
ieee80211_crypto_hw_decrypt(struct ieee80211_rx_data *rx)
{
	if (rx->sta && rx->sta->cipher_scheme)
		return ieee80211_crypto_cs_decrypt(rx);

	return RX_DROP_UNUSABLE;
}