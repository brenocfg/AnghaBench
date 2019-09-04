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
struct ath10k_vif {int /*<<< orphan*/  ar; int /*<<< orphan*/  spectral_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPECTRAL_DISABLED ; 
 int ath10k_spectral_scan_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ath10k_spectral_vif_stop(struct ath10k_vif *arvif)
{
	if (!arvif->spectral_enabled)
		return 0;

	return ath10k_spectral_scan_config(arvif->ar, SPECTRAL_DISABLED);
}