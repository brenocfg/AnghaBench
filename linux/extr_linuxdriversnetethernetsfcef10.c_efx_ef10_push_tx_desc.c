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
 int /*<<< orphan*/  EFX_POPULATE_OWORD_1 (TYPE_1__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ERF_DZ_TX_DESC_WPTR ; 
 int /*<<< orphan*/  ER_DZ_TX_DESC_UPD ; 
 int /*<<< orphan*/  efx_writeo_page (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void efx_ef10_push_tx_desc(struct efx_tx_queue *tx_queue,
					 const efx_qword_t *txd)
{
	unsigned int write_ptr;
	efx_oword_t reg;

	write_ptr = tx_queue->write_count & tx_queue->ptr_mask;
	EFX_POPULATE_OWORD_1(reg, ERF_DZ_TX_DESC_WPTR, write_ptr);
	reg.qword[0] = *txd;
	efx_writeo_page(tx_queue->efx, &reg,
			ER_DZ_TX_DESC_UPD, tx_queue->queue);
}