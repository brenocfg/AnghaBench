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
struct ef4_tx_queue {unsigned int write_count; unsigned int ptr_mask; int /*<<< orphan*/  queue; int /*<<< orphan*/  efx; } ;
typedef  int /*<<< orphan*/  ef4_dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_POPULATE_DWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESC_WPTR_DWORD ; 
 int /*<<< orphan*/  FR_AZ_TX_DESC_UPD_DWORD_P0 ; 
 int /*<<< orphan*/  ef4_writed_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ef4_farch_notify_tx_desc(struct ef4_tx_queue *tx_queue)
{
	unsigned write_ptr;
	ef4_dword_t reg;

	write_ptr = tx_queue->write_count & tx_queue->ptr_mask;
	EF4_POPULATE_DWORD_1(reg, FRF_AZ_TX_DESC_WPTR_DWORD, write_ptr);
	ef4_writed_page(tx_queue->efx, &reg,
			FR_AZ_TX_DESC_UPD_DWORD_P0, tx_queue->queue);
}