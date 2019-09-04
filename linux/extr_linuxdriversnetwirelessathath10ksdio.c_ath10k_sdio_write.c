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
typedef  int /*<<< orphan*/  u32 ;
struct sdio_func {int dummy; } ;
struct ath10k_sdio {struct sdio_func* func; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_SDIO ; 
 int /*<<< orphan*/  ATH10K_DBG_SDIO_DUMP ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  ath10k_dbg_dump (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,void const*,size_t) ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int sdio_memcpy_toio (struct sdio_func*,int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 

__attribute__((used)) static int ath10k_sdio_write(struct ath10k *ar, u32 addr, const void *buf, size_t len)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	struct sdio_func *func = ar_sdio->func;
	int ret;

	sdio_claim_host(func);

	/* For some reason toio() doesn't have const for the buffer, need
	 * an ugly hack to workaround that.
	 */
	ret = sdio_memcpy_toio(func, addr, (void *)buf, len);
	if (ret) {
		ath10k_warn(ar, "failed to write to address 0x%x: %d\n",
			    addr, ret);
		goto out;
	}

	ath10k_dbg(ar, ATH10K_DBG_SDIO, "sdio write addr 0x%x buf 0x%p len %zu\n",
		   addr, buf, len);
	ath10k_dbg_dump(ar, ATH10K_DBG_SDIO_DUMP, NULL, "sdio write ", buf, len);

out:
	sdio_release_host(func);

	return ret;
}