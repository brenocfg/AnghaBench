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
struct efx_rx_page_state {int dummy; } ;
struct efx_nic {int rx_page_buf_step; int rx_bufs_per_page; int rx_buffer_order; int rx_buffer_truesize; int /*<<< orphan*/  rx_pages_per_batch; scalar_t__ rx_ip_align; scalar_t__ rx_dma_len; } ;

/* Variables and functions */
 int ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EFX_RX_BUF_ALIGNMENT ; 
 int /*<<< orphan*/  EFX_RX_PREFERRED_BATCH ; 
 int PAGE_SIZE ; 

void efx_rx_config_page_split(struct efx_nic *efx)
{
	efx->rx_page_buf_step = ALIGN(efx->rx_dma_len + efx->rx_ip_align,
				      EFX_RX_BUF_ALIGNMENT);
	efx->rx_bufs_per_page = efx->rx_buffer_order ? 1 :
		((PAGE_SIZE - sizeof(struct efx_rx_page_state)) /
		 efx->rx_page_buf_step);
	efx->rx_buffer_truesize = (PAGE_SIZE << efx->rx_buffer_order) /
		efx->rx_bufs_per_page;
	efx->rx_pages_per_batch = DIV_ROUND_UP(EFX_RX_PREFERRED_BATCH,
					       efx->rx_bufs_per_page);
}