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
struct niu_bmac_stats {int /*<<< orphan*/  pause_received; int /*<<< orphan*/  pause_on_state; int /*<<< orphan*/  pause_off_state; int /*<<< orphan*/  rx_len_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_align_errors; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  rx_overflows; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_max_pkt_size_errors; int /*<<< orphan*/  tx_underflow_errors; } ;
struct TYPE_2__ {struct niu_bmac_stats bmac; } ;
struct niu {TYPE_1__ mac_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMAC_CTRL_STATUS ; 
 int BMAC_CTRL_STATUS_NOPAUSE ; 
 int BMAC_CTRL_STATUS_PAUSE ; 
 int BMAC_CTRL_STATUS_PAUSE_RECV ; 
 scalar_t__ BRXMAC_ALIGN_ERR_CNT_COUNT ; 
 scalar_t__ BRXMAC_CODE_VIOL_ERR_CNT_COUNT ; 
 scalar_t__ BRXMAC_FRAME_CNT_COUNT ; 
 int /*<<< orphan*/  BRXMAC_STATUS ; 
 int BRXMAC_STATUS_ALIGN_ERR_EXP ; 
 int BRXMAC_STATUS_CRC_ERR_EXP ; 
 int BRXMAC_STATUS_FRAME_CNT_EXP ; 
 int BRXMAC_STATUS_LEN_ERR_EXP ; 
 int BRXMAC_STATUS_OVERFLOW ; 
 scalar_t__ BTXMAC_BYTE_CNT_COUNT ; 
 scalar_t__ BTXMAC_FRM_CNT_COUNT ; 
 int /*<<< orphan*/  BTXMAC_STATUS ; 
 int BTXMAC_STATUS_BYTE_CNT_EXP ; 
 int BTXMAC_STATUS_FRAME_CNT_EXP ; 
 int BTXMAC_STATUS_MAX_PKT_ERR ; 
 int BTXMAC_STATUS_UNDERRUN ; 
 int nr64_mac (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_bmac_interrupt(struct niu *np)
{
	struct niu_bmac_stats *mp = &np->mac_stats.bmac;
	u64 val;

	val = nr64_mac(BTXMAC_STATUS);
	if (val & BTXMAC_STATUS_UNDERRUN)
		mp->tx_underflow_errors++;
	if (val & BTXMAC_STATUS_MAX_PKT_ERR)
		mp->tx_max_pkt_size_errors++;
	if (val & BTXMAC_STATUS_BYTE_CNT_EXP)
		mp->tx_bytes += BTXMAC_BYTE_CNT_COUNT;
	if (val & BTXMAC_STATUS_FRAME_CNT_EXP)
		mp->tx_frames += BTXMAC_FRM_CNT_COUNT;

	val = nr64_mac(BRXMAC_STATUS);
	if (val & BRXMAC_STATUS_OVERFLOW)
		mp->rx_overflows++;
	if (val & BRXMAC_STATUS_FRAME_CNT_EXP)
		mp->rx_frames += BRXMAC_FRAME_CNT_COUNT;
	if (val & BRXMAC_STATUS_ALIGN_ERR_EXP)
		mp->rx_align_errors += BRXMAC_ALIGN_ERR_CNT_COUNT;
	if (val & BRXMAC_STATUS_CRC_ERR_EXP)
		mp->rx_crc_errors += BRXMAC_ALIGN_ERR_CNT_COUNT;
	if (val & BRXMAC_STATUS_LEN_ERR_EXP)
		mp->rx_len_errors += BRXMAC_CODE_VIOL_ERR_CNT_COUNT;

	val = nr64_mac(BMAC_CTRL_STATUS);
	if (val & BMAC_CTRL_STATUS_NOPAUSE)
		mp->pause_off_state++;
	if (val & BMAC_CTRL_STATUS_PAUSE)
		mp->pause_on_state++;
	if (val & BMAC_CTRL_STATUS_PAUSE_RECV)
		mp->pause_received++;
}