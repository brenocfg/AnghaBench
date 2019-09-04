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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBOX_WINDOW_DATA_ADDRESS ; 
 int /*<<< orphan*/  MBOX_WINDOW_READ_ADDR_ADDRESS ; 
 int ath10k_sdio_read (struct ath10k*,int /*<<< orphan*/ ,void*,size_t) ; 
 int ath10k_sdio_write32 (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 

__attribute__((used)) static int ath10k_sdio_hif_diag_read(struct ath10k *ar, u32 address, void *buf,
				     size_t buf_len)
{
	int ret;

	/* set window register to start read cycle */
	ret = ath10k_sdio_write32(ar, MBOX_WINDOW_READ_ADDR_ADDRESS, address);
	if (ret) {
		ath10k_warn(ar, "failed to set mbox window read address: %d", ret);
		return ret;
	}

	/* read the data */
	ret = ath10k_sdio_read(ar, MBOX_WINDOW_DATA_ADDRESS, buf, buf_len);
	if (ret) {
		ath10k_warn(ar, "failed to read from mbox window data address: %d\n",
			    ret);
		return ret;
	}

	return 0;
}