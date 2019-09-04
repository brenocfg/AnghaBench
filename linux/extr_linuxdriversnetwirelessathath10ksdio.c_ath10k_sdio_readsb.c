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
typedef  int /*<<< orphan*/  u32 ;
struct sdio_func {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  block_size; } ;
struct ath10k_sdio {TYPE_1__ mbox_info; struct sdio_func* func; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_SDIO ; 
 int /*<<< orphan*/  ATH10K_DBG_SDIO_DUMP ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  ath10k_dbg_dump (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,void*,size_t) ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int) ; 
 size_t round_down (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int sdio_readsb (struct sdio_func*,void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 

__attribute__((used)) static int ath10k_sdio_readsb(struct ath10k *ar, u32 addr, void *buf, size_t len)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	struct sdio_func *func = ar_sdio->func;
	int ret;

	sdio_claim_host(func);

	len = round_down(len, ar_sdio->mbox_info.block_size);

	ret = sdio_readsb(func, buf, addr, len);
	if (ret) {
		ath10k_warn(ar, "failed to read from fixed (sb) address 0x%x: %d\n",
			    addr, ret);
		goto out;
	}

	ath10k_dbg(ar, ATH10K_DBG_SDIO, "sdio readsb addr 0x%x buf 0x%p len %zu\n",
		   addr, buf, len);
	ath10k_dbg_dump(ar, ATH10K_DBG_SDIO_DUMP, NULL, "sdio readsb ", buf, len);

out:
	sdio_release_host(func);

	return ret;
}