#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct efx_tx_queue {unsigned int write_count; unsigned int ptr_mask; int /*<<< orphan*/  queue; int /*<<< orphan*/  efx; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;
struct TYPE_4__ {int /*<<< orphan*/ * qword; } ;
typedef  TYPE_1__ efx_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_2 (TYPE_1__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ FRF_AZ_TX_DESC_LBN ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESC_PUSH_CMD ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESC_WPTR ; 
 scalar_t__ FR_AA_TX_DESC_UPD_KER ; 
 scalar_t__ FR_BZ_TX_DESC_UPD_P0 ; 
 int /*<<< orphan*/  efx_writeo_page (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void efx_farch_push_tx_desc(struct efx_tx_queue *tx_queue,
					  const efx_qword_t *txd)
{
	unsigned write_ptr;
	efx_oword_t reg;

	BUILD_BUG_ON(FRF_AZ_TX_DESC_LBN != 0);
	BUILD_BUG_ON(FR_AA_TX_DESC_UPD_KER != FR_BZ_TX_DESC_UPD_P0);

	write_ptr = tx_queue->write_count & tx_queue->ptr_mask;
	EFX_POPULATE_OWORD_2(reg, FRF_AZ_TX_DESC_PUSH_CMD, true,
			     FRF_AZ_TX_DESC_WPTR, write_ptr);
	reg.qword[0] = *txd;
	efx_writeo_page(tx_queue->efx, &reg,
			FR_BZ_TX_DESC_UPD_P0, tx_queue->queue);
}