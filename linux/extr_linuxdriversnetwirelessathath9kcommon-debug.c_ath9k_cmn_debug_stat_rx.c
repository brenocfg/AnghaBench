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
struct ath_rx_status {int rs_status; size_t rs_phyerr; scalar_t__ rs_datalen; } ;
struct ath_rx_stats {int /*<<< orphan*/ * phy_err_stats; int /*<<< orphan*/  phy_err; int /*<<< orphan*/  decrypt_busy_err; int /*<<< orphan*/  post_delim_crc_err; int /*<<< orphan*/  pre_delim_crc_err; int /*<<< orphan*/  mic_err; int /*<<< orphan*/  decrypt_crc_err; int /*<<< orphan*/  crc_err; int /*<<< orphan*/  rx_bytes_all; int /*<<< orphan*/  rx_pkts_all; } ;

/* Variables and functions */
 size_t ATH9K_PHYERR_MAX ; 
 int ATH9K_RXERR_CRC ; 
 int ATH9K_RXERR_DECRYPT ; 
 int ATH9K_RXERR_MIC ; 
 int ATH9K_RXERR_PHY ; 
 int ATH9K_RX_DECRYPT_BUSY ; 
 int ATH9K_RX_DELIM_CRC_POST ; 
 int ATH9K_RX_DELIM_CRC_PRE ; 

void ath9k_cmn_debug_stat_rx(struct ath_rx_stats *rxstats,
			     struct ath_rx_status *rs)
{
#define RX_PHY_ERR_INC(c) rxstats->phy_err_stats[c]++
#define RX_CMN_STAT_INC(c) (rxstats->c++)

	RX_CMN_STAT_INC(rx_pkts_all);
	rxstats->rx_bytes_all += rs->rs_datalen;

	if (rs->rs_status & ATH9K_RXERR_CRC)
		RX_CMN_STAT_INC(crc_err);
	if (rs->rs_status & ATH9K_RXERR_DECRYPT)
		RX_CMN_STAT_INC(decrypt_crc_err);
	if (rs->rs_status & ATH9K_RXERR_MIC)
		RX_CMN_STAT_INC(mic_err);
	if (rs->rs_status & ATH9K_RX_DELIM_CRC_PRE)
		RX_CMN_STAT_INC(pre_delim_crc_err);
	if (rs->rs_status & ATH9K_RX_DELIM_CRC_POST)
		RX_CMN_STAT_INC(post_delim_crc_err);
	if (rs->rs_status & ATH9K_RX_DECRYPT_BUSY)
		RX_CMN_STAT_INC(decrypt_busy_err);

	if (rs->rs_status & ATH9K_RXERR_PHY) {
		RX_CMN_STAT_INC(phy_err);
		if (rs->rs_phyerr < ATH9K_PHYERR_MAX)
			RX_PHY_ERR_INC(rs->rs_phyerr);
	}

#undef RX_CMN_STAT_INC
#undef RX_PHY_ERR_INC
}