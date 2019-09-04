#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct efx_rx_queue {TYPE_2__* efx; } ;
struct efx_rx_buffer {int /*<<< orphan*/  dma_addr; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {scalar_t__ rx_buffer_padding; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_POPULATE_QWORD_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSF_AZ_RX_KER_BUF_ADDR ; 
 int /*<<< orphan*/  FSF_AZ_RX_KER_BUF_REGION ; 
 int /*<<< orphan*/  FSF_AZ_RX_KER_BUF_SIZE ; 
 struct efx_rx_buffer* efx_rx_buffer (struct efx_rx_queue*,unsigned int) ; 
 int /*<<< orphan*/ * efx_rx_desc (struct efx_rx_queue*,unsigned int) ; 

__attribute__((used)) static inline void
efx_farch_build_rx_desc(struct efx_rx_queue *rx_queue, unsigned index)
{
	struct efx_rx_buffer *rx_buf;
	efx_qword_t *rxd;

	rxd = efx_rx_desc(rx_queue, index);
	rx_buf = efx_rx_buffer(rx_queue, index);
	EFX_POPULATE_QWORD_3(*rxd,
			     FSF_AZ_RX_KER_BUF_SIZE,
			     rx_buf->len -
			     rx_queue->efx->type->rx_buffer_padding,
			     FSF_AZ_RX_KER_BUF_REGION, 0,
			     FSF_AZ_RX_KER_BUF_ADDR, rx_buf->dma_addr);
}