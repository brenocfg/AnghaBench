#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ath9k_htc_priv {TYPE_3__* hw; TYPE_2__* ah; } ;
struct TYPE_6__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_4__ {int hw_caps; } ;
struct TYPE_5__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int ATH9K_HW_CAP_RFSILENT ; 
 int /*<<< orphan*/  wiphy_rfkill_start_polling (int /*<<< orphan*/ ) ; 

void ath9k_start_rfkill_poll(struct ath9k_htc_priv *priv)
{
	if (priv->ah->caps.hw_caps & ATH9K_HW_CAP_RFSILENT)
		wiphy_rfkill_start_polling(priv->hw->wiphy);
}