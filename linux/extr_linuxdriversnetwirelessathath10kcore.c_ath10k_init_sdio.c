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
typedef  int u32 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int HI_ACS_FLAGS_ALT_DATA_CREDIT_SIZE ; 
 int HI_ACS_FLAGS_SDIO_REDUCE_TX_COMPL_SET ; 
 int HI_ACS_FLAGS_SDIO_SWAP_MAILBOX_SET ; 
 int /*<<< orphan*/  ath10k_bmi_read32 (struct ath10k*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ath10k_bmi_write32 (struct ath10k*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hi_acs_flags ; 
 int /*<<< orphan*/  hi_mbox_io_block_sz ; 
 int /*<<< orphan*/  hi_mbox_isr_yield_limit ; 

__attribute__((used)) static void ath10k_init_sdio(struct ath10k *ar)
{
	u32 param = 0;

	ath10k_bmi_write32(ar, hi_mbox_io_block_sz, 256);
	ath10k_bmi_write32(ar, hi_mbox_isr_yield_limit, 99);
	ath10k_bmi_read32(ar, hi_acs_flags, &param);

	param |= (HI_ACS_FLAGS_SDIO_SWAP_MAILBOX_SET |
		  HI_ACS_FLAGS_SDIO_REDUCE_TX_COMPL_SET |
		  HI_ACS_FLAGS_ALT_DATA_CREDIT_SIZE);

	ath10k_bmi_write32(ar, hi_acs_flags, param);
}