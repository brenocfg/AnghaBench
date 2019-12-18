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
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {int tx_type; int rx_filter; scalar_t__ flags; } ;
typedef  enum hwtstamp_tx_types { ____Placeholder_hwtstamp_tx_types } hwtstamp_tx_types ;
typedef  enum hwtstamp_rx_filters { ____Placeholder_hwtstamp_rx_filters } hwtstamp_rx_filters ;
typedef  int /*<<< orphan*/  cfg ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ERANGE ; 
#define  HWTSTAMP_FILTER_ALL 146 
#define  HWTSTAMP_FILTER_NONE 145 
#define  HWTSTAMP_FILTER_NTP_ALL 144 
#define  HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ 143 
#define  HWTSTAMP_FILTER_PTP_V1_L4_EVENT 142 
#define  HWTSTAMP_FILTER_PTP_V1_L4_SYNC 141 
#define  HWTSTAMP_FILTER_PTP_V2_DELAY_REQ 140 
#define  HWTSTAMP_FILTER_PTP_V2_EVENT 139 
#define  HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ 138 
#define  HWTSTAMP_FILTER_PTP_V2_L2_EVENT 137 
#define  HWTSTAMP_FILTER_PTP_V2_L2_SYNC 136 
#define  HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ 135 
#define  HWTSTAMP_FILTER_PTP_V2_L4_EVENT 134 
#define  HWTSTAMP_FILTER_PTP_V2_L4_SYNC 133 
#define  HWTSTAMP_FILTER_PTP_V2_SYNC 132 
#define  HWTSTAMP_FILTER_SOME 131 
#define  HWTSTAMP_TX_OFF 130 
#define  HWTSTAMP_TX_ON 129 
#define  HWTSTAMP_TX_ONESTEP_SYNC 128 
 scalar_t__ copy_from_user (struct hwtstamp_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int net_hwtstamp_validate(struct ifreq *ifr)
{
	struct hwtstamp_config cfg;
	enum hwtstamp_tx_types tx_type;
	enum hwtstamp_rx_filters rx_filter;
	int tx_type_valid = 0;
	int rx_filter_valid = 0;

	if (copy_from_user(&cfg, ifr->ifr_data, sizeof(cfg)))
		return -EFAULT;

	if (cfg.flags) /* reserved for future extensions */
		return -EINVAL;

	tx_type = cfg.tx_type;
	rx_filter = cfg.rx_filter;

	switch (tx_type) {
	case HWTSTAMP_TX_OFF:
	case HWTSTAMP_TX_ON:
	case HWTSTAMP_TX_ONESTEP_SYNC:
		tx_type_valid = 1;
		break;
	}

	switch (rx_filter) {
	case HWTSTAMP_FILTER_NONE:
	case HWTSTAMP_FILTER_ALL:
	case HWTSTAMP_FILTER_SOME:
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	case HWTSTAMP_FILTER_NTP_ALL:
		rx_filter_valid = 1;
		break;
	}

	if (!tx_type_valid || !rx_filter_valid)
		return -ERANGE;

	return 0;
}