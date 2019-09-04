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
struct ef4_rx_queue {int /*<<< orphan*/  rxd; struct ef4_nic* efx; } ;
struct ef4_nic {TYPE_1__* type; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;
struct TYPE_2__ {int /*<<< orphan*/  rxd_ptr_tbl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_ZERO_OWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_fini_special_buffer (struct ef4_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ef4_rx_queue_index (struct ef4_rx_queue*) ; 
 int /*<<< orphan*/  ef4_writeo_table (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ef4_farch_rx_fini(struct ef4_rx_queue *rx_queue)
{
	ef4_oword_t rx_desc_ptr;
	struct ef4_nic *efx = rx_queue->efx;

	/* Remove RX descriptor ring from card */
	EF4_ZERO_OWORD(rx_desc_ptr);
	ef4_writeo_table(efx, &rx_desc_ptr, efx->type->rxd_ptr_tbl_base,
			 ef4_rx_queue_index(rx_queue));

	/* Unpin RX descriptor ring */
	ef4_fini_special_buffer(efx, &rx_queue->rxd);
}