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
typedef  int u64 ;
struct niu_xmac_stats {int /*<<< orphan*/  pause_received; int /*<<< orphan*/  pause_on_state; int /*<<< orphan*/  pause_off_state; int /*<<< orphan*/  rx_overflows; int /*<<< orphan*/  rx_underflows; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_len_errors; int /*<<< orphan*/  rx_code_violations; int /*<<< orphan*/  rx_octets; int /*<<< orphan*/  rx_hist_cnt7; int /*<<< orphan*/  rx_hist_cnt6; int /*<<< orphan*/  rx_hist_cnt5; int /*<<< orphan*/  rx_hist_cnt4; int /*<<< orphan*/  rx_hist_cnt3; int /*<<< orphan*/  rx_hist_cnt2; int /*<<< orphan*/  rx_hist_cnt1; int /*<<< orphan*/  rx_bcasts; int /*<<< orphan*/  rx_mcasts; int /*<<< orphan*/  rx_frags; int /*<<< orphan*/  rx_align_errors; int /*<<< orphan*/  rx_link_faults; int /*<<< orphan*/  rx_remote_faults; int /*<<< orphan*/  rx_local_faults; int /*<<< orphan*/  tx_underflow_errors; int /*<<< orphan*/  tx_max_pkt_size_errors; int /*<<< orphan*/  tx_overflow_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_frames; } ;
struct TYPE_2__ {struct niu_xmac_stats xmac; } ;
struct niu {TYPE_1__ mac_stats; } ;

/* Variables and functions */
 scalar_t__ LINK_FAULT_CNT_COUNT ; 
 scalar_t__ RXMAC_ALIGN_ERR_CNT_COUNT ; 
 scalar_t__ RXMAC_BC_FRM_CNT_COUNT ; 
 scalar_t__ RXMAC_BT_CNT_COUNT ; 
 scalar_t__ RXMAC_CD_VIO_CNT_COUNT ; 
 scalar_t__ RXMAC_CRC_ER_CNT_COUNT ; 
 scalar_t__ RXMAC_FRAG_CNT_COUNT ; 
 scalar_t__ RXMAC_HIST_CNT1_COUNT ; 
 scalar_t__ RXMAC_HIST_CNT2_COUNT ; 
 scalar_t__ RXMAC_HIST_CNT3_COUNT ; 
 scalar_t__ RXMAC_HIST_CNT4_COUNT ; 
 scalar_t__ RXMAC_HIST_CNT5_COUNT ; 
 scalar_t__ RXMAC_HIST_CNT6_COUNT ; 
 scalar_t__ RXMAC_HIST_CNT7_COUNT ; 
 scalar_t__ RXMAC_MC_FRM_CNT_COUNT ; 
 scalar_t__ RXMAC_MPSZER_CNT_COUNT ; 
 scalar_t__ TXMAC_BYTE_CNT_COUNT ; 
 scalar_t__ TXMAC_FRM_CNT_COUNT ; 
 int /*<<< orphan*/  XMAC_FC_STAT ; 
 int XMAC_FC_STAT_RX_MAC_RPAUSE ; 
 int XMAC_FC_STAT_TX_MAC_NPAUSE ; 
 int XMAC_FC_STAT_TX_MAC_PAUSE ; 
 int /*<<< orphan*/  XRXMAC_STATUS ; 
 int XRXMAC_STATUS_ALIGNERR_CNT_EXP ; 
 int XRXMAC_STATUS_CRCERR_CNT_EXP ; 
 int XRXMAC_STATUS_CVIOLERR_CNT_EXP ; 
 int XRXMAC_STATUS_LCL_FLT_STATUS ; 
 int XRXMAC_STATUS_LENERR_CNT_EXP ; 
 int XRXMAC_STATUS_LFLT_CNT_EXP ; 
 int XRXMAC_STATUS_RFLT_DET ; 
 int XRXMAC_STATUS_RXBCAST_CNT_EXP ; 
 int XRXMAC_STATUS_RXFRAG_CNT_EXP ; 
 int XRXMAC_STATUS_RXHIST1_CNT_EXP ; 
 int XRXMAC_STATUS_RXHIST2_CNT_EXP ; 
 int XRXMAC_STATUS_RXHIST3_CNT_EXP ; 
 int XRXMAC_STATUS_RXHIST4_CNT_EXP ; 
 int XRXMAC_STATUS_RXHIST5_CNT_EXP ; 
 int XRXMAC_STATUS_RXHIST6_CNT_EXP ; 
 int XRXMAC_STATUS_RXHIST7_CNT_EXP ; 
 int XRXMAC_STATUS_RXMULTF_CNT_EXP ; 
 int XRXMAC_STATUS_RXOCTET_CNT_EXP ; 
 int XRXMAC_STATUS_RXOFLOW ; 
 int XRXMAC_STATUS_RXUFLOW ; 
 int /*<<< orphan*/  XTXMAC_STATUS ; 
 int XTXMAC_STATUS_BYTE_CNT_EXP ; 
 int XTXMAC_STATUS_FRAME_CNT_EXP ; 
 int XTXMAC_STATUS_MAX_PSIZE_ERR ; 
 int XTXMAC_STATUS_TXFIFO_XFR_ERR ; 
 int XTXMAC_STATUS_TXMAC_OFLOW ; 
 int XTXMAC_STATUS_TXMAC_UFLOW ; 
 int nr64_mac (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_xmac_interrupt(struct niu *np)
{
	struct niu_xmac_stats *mp = &np->mac_stats.xmac;
	u64 val;

	val = nr64_mac(XTXMAC_STATUS);
	if (val & XTXMAC_STATUS_FRAME_CNT_EXP)
		mp->tx_frames += TXMAC_FRM_CNT_COUNT;
	if (val & XTXMAC_STATUS_BYTE_CNT_EXP)
		mp->tx_bytes += TXMAC_BYTE_CNT_COUNT;
	if (val & XTXMAC_STATUS_TXFIFO_XFR_ERR)
		mp->tx_fifo_errors++;
	if (val & XTXMAC_STATUS_TXMAC_OFLOW)
		mp->tx_overflow_errors++;
	if (val & XTXMAC_STATUS_MAX_PSIZE_ERR)
		mp->tx_max_pkt_size_errors++;
	if (val & XTXMAC_STATUS_TXMAC_UFLOW)
		mp->tx_underflow_errors++;

	val = nr64_mac(XRXMAC_STATUS);
	if (val & XRXMAC_STATUS_LCL_FLT_STATUS)
		mp->rx_local_faults++;
	if (val & XRXMAC_STATUS_RFLT_DET)
		mp->rx_remote_faults++;
	if (val & XRXMAC_STATUS_LFLT_CNT_EXP)
		mp->rx_link_faults += LINK_FAULT_CNT_COUNT;
	if (val & XRXMAC_STATUS_ALIGNERR_CNT_EXP)
		mp->rx_align_errors += RXMAC_ALIGN_ERR_CNT_COUNT;
	if (val & XRXMAC_STATUS_RXFRAG_CNT_EXP)
		mp->rx_frags += RXMAC_FRAG_CNT_COUNT;
	if (val & XRXMAC_STATUS_RXMULTF_CNT_EXP)
		mp->rx_mcasts += RXMAC_MC_FRM_CNT_COUNT;
	if (val & XRXMAC_STATUS_RXBCAST_CNT_EXP)
		mp->rx_bcasts += RXMAC_BC_FRM_CNT_COUNT;
	if (val & XRXMAC_STATUS_RXBCAST_CNT_EXP)
		mp->rx_bcasts += RXMAC_BC_FRM_CNT_COUNT;
	if (val & XRXMAC_STATUS_RXHIST1_CNT_EXP)
		mp->rx_hist_cnt1 += RXMAC_HIST_CNT1_COUNT;
	if (val & XRXMAC_STATUS_RXHIST2_CNT_EXP)
		mp->rx_hist_cnt2 += RXMAC_HIST_CNT2_COUNT;
	if (val & XRXMAC_STATUS_RXHIST3_CNT_EXP)
		mp->rx_hist_cnt3 += RXMAC_HIST_CNT3_COUNT;
	if (val & XRXMAC_STATUS_RXHIST4_CNT_EXP)
		mp->rx_hist_cnt4 += RXMAC_HIST_CNT4_COUNT;
	if (val & XRXMAC_STATUS_RXHIST5_CNT_EXP)
		mp->rx_hist_cnt5 += RXMAC_HIST_CNT5_COUNT;
	if (val & XRXMAC_STATUS_RXHIST6_CNT_EXP)
		mp->rx_hist_cnt6 += RXMAC_HIST_CNT6_COUNT;
	if (val & XRXMAC_STATUS_RXHIST7_CNT_EXP)
		mp->rx_hist_cnt7 += RXMAC_HIST_CNT7_COUNT;
	if (val & XRXMAC_STATUS_RXOCTET_CNT_EXP)
		mp->rx_octets += RXMAC_BT_CNT_COUNT;
	if (val & XRXMAC_STATUS_CVIOLERR_CNT_EXP)
		mp->rx_code_violations += RXMAC_CD_VIO_CNT_COUNT;
	if (val & XRXMAC_STATUS_LENERR_CNT_EXP)
		mp->rx_len_errors += RXMAC_MPSZER_CNT_COUNT;
	if (val & XRXMAC_STATUS_CRCERR_CNT_EXP)
		mp->rx_crc_errors += RXMAC_CRC_ER_CNT_COUNT;
	if (val & XRXMAC_STATUS_RXUFLOW)
		mp->rx_underflows++;
	if (val & XRXMAC_STATUS_RXOFLOW)
		mp->rx_overflows++;

	val = nr64_mac(XMAC_FC_STAT);
	if (val & XMAC_FC_STAT_TX_MAC_NPAUSE)
		mp->pause_off_state++;
	if (val & XMAC_FC_STAT_TX_MAC_PAUSE)
		mp->pause_on_state++;
	if (val & XMAC_FC_STAT_RX_MAC_RPAUSE)
		mp->pause_received++;
}