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
struct TYPE_6__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  index; } ;
struct ef4_tx_queue {int queue; TYPE_3__ txd; TYPE_1__* channel; struct ef4_nic* efx; } ;
struct ef4_nic {TYPE_2__* type; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;
struct TYPE_5__ {int /*<<< orphan*/  txd_ptr_tbl_base; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EF4_MAX_TX_QUEUES ; 
 int /*<<< orphan*/  EF4_POPULATE_OWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EF4_POPULATE_OWORD_10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ EF4_REV_FALCON_B0 ; 
 int /*<<< orphan*/  EF4_SET_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int EF4_TXQ_TYPE_HIGHPRI ; 
 int EF4_TXQ_TYPE_OFFLOAD ; 
 int /*<<< orphan*/  FFE_BZ_TX_PACE_OFF ; 
 int /*<<< orphan*/  FFE_BZ_TX_PACE_RESERVED ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_BUF_BASE_ID ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_EN ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_EVQ_ID ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_LABEL ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_OWNER_ID ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_SIZE ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_TYPE ; 
 int /*<<< orphan*/  FRF_AZ_TX_ISCSI_DDIG_EN ; 
 int /*<<< orphan*/  FRF_AZ_TX_ISCSI_HDIG_EN ; 
 int /*<<< orphan*/  FRF_BZ_TX_IP_CHKSM_DIS ; 
 int /*<<< orphan*/  FRF_BZ_TX_NON_IP_DROP_DIS ; 
 int /*<<< orphan*/  FRF_BZ_TX_PACE ; 
 int /*<<< orphan*/  FRF_BZ_TX_TCP_CHKSM_DIS ; 
 int /*<<< orphan*/  FR_AA_TX_CHKSM_CFG ; 
 int /*<<< orphan*/  FR_BZ_TX_PACE_TBL ; 
 int /*<<< orphan*/  __clear_bit_le (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit_le (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ef4_init_special_buffer (struct ef4_nic*,TYPE_3__*) ; 
 scalar_t__ ef4_nic_rev (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_reado (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_writeo (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_writeo_table (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void ef4_farch_tx_init(struct ef4_tx_queue *tx_queue)
{
	struct ef4_nic *efx = tx_queue->efx;
	ef4_oword_t reg;

	/* Pin TX descriptor ring */
	ef4_init_special_buffer(efx, &tx_queue->txd);

	/* Push TX descriptor ring to card */
	EF4_POPULATE_OWORD_10(reg,
			      FRF_AZ_TX_DESCQ_EN, 1,
			      FRF_AZ_TX_ISCSI_DDIG_EN, 0,
			      FRF_AZ_TX_ISCSI_HDIG_EN, 0,
			      FRF_AZ_TX_DESCQ_BUF_BASE_ID, tx_queue->txd.index,
			      FRF_AZ_TX_DESCQ_EVQ_ID,
			      tx_queue->channel->channel,
			      FRF_AZ_TX_DESCQ_OWNER_ID, 0,
			      FRF_AZ_TX_DESCQ_LABEL, tx_queue->queue,
			      FRF_AZ_TX_DESCQ_SIZE,
			      __ffs(tx_queue->txd.entries),
			      FRF_AZ_TX_DESCQ_TYPE, 0,
			      FRF_BZ_TX_NON_IP_DROP_DIS, 1);

	if (ef4_nic_rev(efx) >= EF4_REV_FALCON_B0) {
		int csum = tx_queue->queue & EF4_TXQ_TYPE_OFFLOAD;
		EF4_SET_OWORD_FIELD(reg, FRF_BZ_TX_IP_CHKSM_DIS, !csum);
		EF4_SET_OWORD_FIELD(reg, FRF_BZ_TX_TCP_CHKSM_DIS,
				    !csum);
	}

	ef4_writeo_table(efx, &reg, efx->type->txd_ptr_tbl_base,
			 tx_queue->queue);

	if (ef4_nic_rev(efx) < EF4_REV_FALCON_B0) {
		/* Only 128 bits in this register */
		BUILD_BUG_ON(EF4_MAX_TX_QUEUES > 128);

		ef4_reado(efx, &reg, FR_AA_TX_CHKSM_CFG);
		if (tx_queue->queue & EF4_TXQ_TYPE_OFFLOAD)
			__clear_bit_le(tx_queue->queue, &reg);
		else
			__set_bit_le(tx_queue->queue, &reg);
		ef4_writeo(efx, &reg, FR_AA_TX_CHKSM_CFG);
	}

	if (ef4_nic_rev(efx) >= EF4_REV_FALCON_B0) {
		EF4_POPULATE_OWORD_1(reg,
				     FRF_BZ_TX_PACE,
				     (tx_queue->queue & EF4_TXQ_TYPE_HIGHPRI) ?
				     FFE_BZ_TX_PACE_OFF :
				     FFE_BZ_TX_PACE_RESERVED);
		ef4_writeo_table(efx, &reg, FR_BZ_TX_PACE_TBL,
				 tx_queue->queue);
	}
}