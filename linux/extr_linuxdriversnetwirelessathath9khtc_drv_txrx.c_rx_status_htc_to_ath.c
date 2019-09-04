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
struct ath_rx_status {int /*<<< orphan*/  rs_num_delims; int /*<<< orphan*/  rs_moreaggr; int /*<<< orphan*/  rs_isaggr; int /*<<< orphan*/  rs_rssi_ext; int /*<<< orphan*/  rs_rssi_ctl; int /*<<< orphan*/  rs_more; int /*<<< orphan*/  rs_antenna; int /*<<< orphan*/  rs_rate; int /*<<< orphan*/  rs_keyix; int /*<<< orphan*/  rs_rssi; int /*<<< orphan*/  rs_phyerr; int /*<<< orphan*/  rs_status; int /*<<< orphan*/  rs_datalen; } ;
struct ath_htc_rx_status {int /*<<< orphan*/  rs_num_delims; int /*<<< orphan*/  rs_moreaggr; int /*<<< orphan*/  rs_isaggr; int /*<<< orphan*/  rs_rssi_ext; int /*<<< orphan*/  rs_rssi_ctl; int /*<<< orphan*/  rs_more; int /*<<< orphan*/  rs_antenna; int /*<<< orphan*/  rs_rate; int /*<<< orphan*/  rs_keyix; int /*<<< orphan*/  rs_rssi; int /*<<< orphan*/  rs_phyerr; int /*<<< orphan*/  rs_status; int /*<<< orphan*/  rs_datalen; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_htc_flag (struct ath_rx_status*,struct ath_htc_rx_status*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rx_status_htc_to_ath(struct ath_rx_status *rx_stats,
				 struct ath_htc_rx_status *rxstatus)
{
	rx_stats->rs_datalen	= be16_to_cpu(rxstatus->rs_datalen);
	rx_stats->rs_status	= rxstatus->rs_status;
	rx_stats->rs_phyerr	= rxstatus->rs_phyerr;
	rx_stats->rs_rssi	= rxstatus->rs_rssi;
	rx_stats->rs_keyix	= rxstatus->rs_keyix;
	rx_stats->rs_rate	= rxstatus->rs_rate;
	rx_stats->rs_antenna	= rxstatus->rs_antenna;
	rx_stats->rs_more	= rxstatus->rs_more;

	memcpy(rx_stats->rs_rssi_ctl, rxstatus->rs_rssi_ctl,
		sizeof(rx_stats->rs_rssi_ctl));
	memcpy(rx_stats->rs_rssi_ext, rxstatus->rs_rssi_ext,
		sizeof(rx_stats->rs_rssi_ext));

	rx_stats->rs_isaggr	= rxstatus->rs_isaggr;
	rx_stats->rs_moreaggr	= rxstatus->rs_moreaggr;
	rx_stats->rs_num_delims	= rxstatus->rs_num_delims;
	convert_htc_flag(rx_stats, rxstatus);
}