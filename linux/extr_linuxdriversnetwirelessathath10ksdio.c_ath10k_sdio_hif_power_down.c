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
struct ath10k_sdio {int is_disabled; int /*<<< orphan*/  func; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int sdio_disable_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_sdio_hif_power_down(struct ath10k *ar)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	int ret;

	if (ar_sdio->is_disabled)
		return;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "sdio power off\n");

	/* Disable the card */
	sdio_claim_host(ar_sdio->func);
	ret = sdio_disable_func(ar_sdio->func);
	sdio_release_host(ar_sdio->func);

	if (ret)
		ath10k_warn(ar, "unable to disable sdio function: %d\n", ret);

	ar_sdio->is_disabled = true;
}