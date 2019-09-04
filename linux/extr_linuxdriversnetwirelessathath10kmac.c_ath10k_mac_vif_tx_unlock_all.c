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
struct ath10k_vif {int dummy; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  ath10k_mac_vif_tx_unlock (struct ath10k_vif*,int) ; 

__attribute__((used)) static void ath10k_mac_vif_tx_unlock_all(struct ath10k_vif *arvif)
{
	int i;

	for (i = 0; i < BITS_PER_LONG; i++)
		ath10k_mac_vif_tx_unlock(arvif, i);
}