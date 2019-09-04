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
struct sdio_func {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; int /*<<< orphan*/  num; } ;
struct ath10k_sdio {int /*<<< orphan*/  wr_async_work; struct ath10k* ar; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  ath10k_core_destroy (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_core_unregister (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_sdio_hif_disable_intrs (struct ath10k*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct ath10k_sdio* sdio_get_drvdata (struct sdio_func*) ; 

__attribute__((used)) static void ath10k_sdio_remove(struct sdio_func *func)
{
	struct ath10k_sdio *ar_sdio = sdio_get_drvdata(func);
	struct ath10k *ar = ar_sdio->ar;

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "sdio removed func %d vendor 0x%x device 0x%x\n",
		   func->num, func->vendor, func->device);

	(void)ath10k_sdio_hif_disable_intrs(ar);
	cancel_work_sync(&ar_sdio->wr_async_work);
	ath10k_core_unregister(ar);
	ath10k_core_destroy(ar);
}