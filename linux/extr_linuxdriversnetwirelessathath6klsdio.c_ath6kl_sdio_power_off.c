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
struct ath6kl_sdio {int is_disabled; int /*<<< orphan*/  func; } ;
struct ath6kl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_BOOT ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*) ; 
 struct ath6kl_sdio* ath6kl_sdio_priv (struct ath6kl*) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int sdio_disable_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_sdio_power_off(struct ath6kl *ar)
{
	struct ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
	int ret;

	if (ar_sdio->is_disabled)
		return 0;

	ath6kl_dbg(ATH6KL_DBG_BOOT, "sdio power off\n");

	/* Disable the card */
	sdio_claim_host(ar_sdio->func);
	ret = sdio_disable_func(ar_sdio->func);
	sdio_release_host(ar_sdio->func);

	if (ret)
		return ret;

	ar_sdio->is_disabled = true;

	return ret;
}