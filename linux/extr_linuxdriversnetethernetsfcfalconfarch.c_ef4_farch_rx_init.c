#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ entries; scalar_t__ index; } ;
struct ef4_rx_queue {TYPE_3__ rxd; scalar_t__ scatter_n; struct ef4_nic* efx; } ;
struct ef4_nic {TYPE_1__* type; int /*<<< orphan*/  net_dev; scalar_t__ rx_scatter; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;
struct TYPE_5__ {int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {int /*<<< orphan*/  rxd_ptr_tbl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_POPULATE_OWORD_10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ EF4_REV_FALCON_B0 ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESCQ_BUF_BASE_ID ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESCQ_EN ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESCQ_EVQ_ID ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESCQ_JUMBO ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESCQ_LABEL ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESCQ_OWNER_ID ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESCQ_SIZE ; 
 int /*<<< orphan*/  FRF_AZ_RX_DESCQ_TYPE ; 
 int /*<<< orphan*/  FRF_AZ_RX_ISCSI_DDIG_EN ; 
 int /*<<< orphan*/  FRF_AZ_RX_ISCSI_HDIG_EN ; 
 int /*<<< orphan*/  __ffs (scalar_t__) ; 
 int /*<<< orphan*/  ef4_init_special_buffer (struct ef4_nic*,TYPE_3__*) ; 
 scalar_t__ ef4_nic_rev (struct ef4_nic*) ; 
 TYPE_2__* ef4_rx_queue_channel (struct ef4_rx_queue*) ; 
 int /*<<< orphan*/  ef4_rx_queue_index (struct ef4_rx_queue*) ; 
 int /*<<< orphan*/  ef4_writeo_table (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void ef4_farch_rx_init(struct ef4_rx_queue *rx_queue)
{
	ef4_oword_t rx_desc_ptr;
	struct ef4_nic *efx = rx_queue->efx;
	bool is_b0 = ef4_nic_rev(efx) >= EF4_REV_FALCON_B0;
	bool iscsi_digest_en = is_b0;
	bool jumbo_en;

	/* For kernel-mode queues in Falcon A1, the JUMBO flag enables
	 * DMA to continue after a PCIe page boundary (and scattering
	 * is not possible).  In Falcon B0 and Siena, it enables
	 * scatter.
	 */
	jumbo_en = !is_b0 || efx->rx_scatter;

	netif_dbg(efx, hw, efx->net_dev,
		  "RX queue %d ring in special buffers %d-%d\n",
		  ef4_rx_queue_index(rx_queue), rx_queue->rxd.index,
		  rx_queue->rxd.index + rx_queue->rxd.entries - 1);

	rx_queue->scatter_n = 0;

	/* Pin RX descriptor ring */
	ef4_init_special_buffer(efx, &rx_queue->rxd);

	/* Push RX descriptor ring to card */
	EF4_POPULATE_OWORD_10(rx_desc_ptr,
			      FRF_AZ_RX_ISCSI_DDIG_EN, iscsi_digest_en,
			      FRF_AZ_RX_ISCSI_HDIG_EN, iscsi_digest_en,
			      FRF_AZ_RX_DESCQ_BUF_BASE_ID, rx_queue->rxd.index,
			      FRF_AZ_RX_DESCQ_EVQ_ID,
			      ef4_rx_queue_channel(rx_queue)->channel,
			      FRF_AZ_RX_DESCQ_OWNER_ID, 0,
			      FRF_AZ_RX_DESCQ_LABEL,
			      ef4_rx_queue_index(rx_queue),
			      FRF_AZ_RX_DESCQ_SIZE,
			      __ffs(rx_queue->rxd.entries),
			      FRF_AZ_RX_DESCQ_TYPE, 0 /* kernel queue */ ,
			      FRF_AZ_RX_DESCQ_JUMBO, jumbo_en,
			      FRF_AZ_RX_DESCQ_EN, 1);
	ef4_writeo_table(efx, &rx_desc_ptr, efx->type->rxd_ptr_tbl_base,
			 ef4_rx_queue_index(rx_queue));
}