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
struct TYPE_2__ {int /*<<< orphan*/  block_mask; } ;
struct ath10k_sdio {TYPE_1__ mbox_info; } ;

/* Variables and functions */
 int __ALIGN_MASK (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ath10k_sdio_calc_txrx_padded_len(struct ath10k_sdio *ar_sdio,
						   size_t len)
{
	return __ALIGN_MASK((len), ar_sdio->mbox_info.block_mask);
}