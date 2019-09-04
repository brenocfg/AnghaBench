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
struct siena_vf {unsigned int index; scalar_t__ evq0_count; int /*<<< orphan*/  buftbl_base; int /*<<< orphan*/  rxq_retry_count; int /*<<< orphan*/  rxq_retry_mask; int /*<<< orphan*/  flush_waitq; scalar_t__ txq_count; scalar_t__ rxq_count; int /*<<< orphan*/  rxq_mask; int /*<<< orphan*/  txq_mask; struct efx_nic* efx; } ;
struct efx_nic {int dummy; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int EFX_VF_BUFTBL_PER_VI ; 
 unsigned int EFX_VI_BASE ; 
 int /*<<< orphan*/  EFX_ZERO_OWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLUSH_RX_QUEUES_IN_QID_OFST ; 
 int /*<<< orphan*/  FRF_AZ_TX_FLUSH_DESCQ ; 
 int /*<<< orphan*/  FRF_AZ_TX_FLUSH_DESCQ_CMD ; 
 int /*<<< orphan*/  FR_AZ_TX_FLUSH_DESCQ ; 
 int /*<<< orphan*/  FR_BZ_EVQ_PTR_TBL ; 
 int /*<<< orphan*/  FR_BZ_RX_DESC_PTR_TBL ; 
 int /*<<< orphan*/  FR_BZ_TIMER_TBL ; 
 int /*<<< orphan*/  FR_BZ_TX_DESC_PTR_TBL ; 
 unsigned int HZ ; 
 int /*<<< orphan*/  MCDI_DECLARE_BUF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCDI_SET_ARRAY_DWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  MC_CMD_FLUSH_RX_QUEUES ; 
 int /*<<< orphan*/  MC_CMD_FLUSH_RX_QUEUES_IN_LEN (unsigned int) ; 
 int /*<<< orphan*/  MC_CMD_FLUSH_RX_QUEUES_IN_LENMAX ; 
 scalar_t__ MC_CMD_FLUSH_RX_QUEUES_IN_QID_OFST_MAXNUM ; 
 int VFDI_RC_ETIMEDOUT ; 
 scalar_t__ VF_MAX_RX_QUEUES ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int efx_mcdi_rpc (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_siena_sriov_bufs (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int efx_vf_size (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_vfdi_flush_clear (struct siena_vf*) ; 
 int /*<<< orphan*/  efx_vfdi_flush_wake (struct siena_vf*) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_writeo_table (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  inbuf ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  siena_finish_flush (struct efx_nic*) ; 
 int /*<<< orphan*/  siena_prepare_flush (struct efx_nic*) ; 
 scalar_t__ test_and_clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int efx_vfdi_fini_all_queues(struct siena_vf *vf)
{
	struct efx_nic *efx = vf->efx;
	efx_oword_t reg;
	unsigned count = efx_vf_size(efx);
	unsigned vf_offset = EFX_VI_BASE + vf->index * efx_vf_size(efx);
	unsigned timeout = HZ;
	unsigned index, rxqs_count;
	MCDI_DECLARE_BUF(inbuf, MC_CMD_FLUSH_RX_QUEUES_IN_LENMAX);
	int rc;

	BUILD_BUG_ON(VF_MAX_RX_QUEUES >
		     MC_CMD_FLUSH_RX_QUEUES_IN_QID_OFST_MAXNUM);

	rtnl_lock();
	siena_prepare_flush(efx);
	rtnl_unlock();

	/* Flush all the initialized queues */
	rxqs_count = 0;
	for (index = 0; index < count; ++index) {
		if (test_bit(index, vf->txq_mask)) {
			EFX_POPULATE_OWORD_2(reg,
					     FRF_AZ_TX_FLUSH_DESCQ_CMD, 1,
					     FRF_AZ_TX_FLUSH_DESCQ,
					     vf_offset + index);
			efx_writeo(efx, &reg, FR_AZ_TX_FLUSH_DESCQ);
		}
		if (test_bit(index, vf->rxq_mask)) {
			MCDI_SET_ARRAY_DWORD(
				inbuf, FLUSH_RX_QUEUES_IN_QID_OFST,
				rxqs_count, vf_offset + index);
			rxqs_count++;
		}
	}

	atomic_set(&vf->rxq_retry_count, 0);
	while (timeout && (vf->rxq_count || vf->txq_count)) {
		rc = efx_mcdi_rpc(efx, MC_CMD_FLUSH_RX_QUEUES, inbuf,
				  MC_CMD_FLUSH_RX_QUEUES_IN_LEN(rxqs_count),
				  NULL, 0, NULL);
		WARN_ON(rc < 0);

		timeout = wait_event_timeout(vf->flush_waitq,
					     efx_vfdi_flush_wake(vf),
					     timeout);
		rxqs_count = 0;
		for (index = 0; index < count; ++index) {
			if (test_and_clear_bit(index, vf->rxq_retry_mask)) {
				atomic_dec(&vf->rxq_retry_count);
				MCDI_SET_ARRAY_DWORD(
					inbuf, FLUSH_RX_QUEUES_IN_QID_OFST,
					rxqs_count, vf_offset + index);
				rxqs_count++;
			}
		}
	}

	rtnl_lock();
	siena_finish_flush(efx);
	rtnl_unlock();

	/* Irrespective of success/failure, fini the queues */
	EFX_ZERO_OWORD(reg);
	for (index = 0; index < count; ++index) {
		efx_writeo_table(efx, &reg, FR_BZ_RX_DESC_PTR_TBL,
				 vf_offset + index);
		efx_writeo_table(efx, &reg, FR_BZ_TX_DESC_PTR_TBL,
				 vf_offset + index);
		efx_writeo_table(efx, &reg, FR_BZ_EVQ_PTR_TBL,
				 vf_offset + index);
		efx_writeo_table(efx, &reg, FR_BZ_TIMER_TBL,
				 vf_offset + index);
	}
	efx_siena_sriov_bufs(efx, vf->buftbl_base, NULL,
			     EFX_VF_BUFTBL_PER_VI * efx_vf_size(efx));
	efx_vfdi_flush_clear(vf);

	vf->evq0_count = 0;

	return timeout ? 0 : VFDI_RC_ETIMEDOUT;
}