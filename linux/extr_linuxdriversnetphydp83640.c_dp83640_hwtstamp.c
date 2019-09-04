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
typedef  int u16 ;
struct phy_device {struct dp83640_private* priv; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {scalar_t__ tx_type; int rx_filter; scalar_t__ flags; } ;
struct dp83640_private {scalar_t__ hwts_tx_en; int hwts_rx_en; int layer; int version; TYPE_1__* clock; } ;
typedef  int /*<<< orphan*/  cfg ;
struct TYPE_2__ {int /*<<< orphan*/  extreg_lock; } ;

/* Variables and functions */
 int CHK_1STEP ; 
 int EFAULT ; 
 int EINVAL ; 
 int ERANGE ; 
#define  HWTSTAMP_FILTER_NONE 140 
#define  HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ 139 
#define  HWTSTAMP_FILTER_PTP_V1_L4_EVENT 138 
#define  HWTSTAMP_FILTER_PTP_V1_L4_SYNC 137 
#define  HWTSTAMP_FILTER_PTP_V2_DELAY_REQ 136 
#define  HWTSTAMP_FILTER_PTP_V2_EVENT 135 
#define  HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ 134 
#define  HWTSTAMP_FILTER_PTP_V2_L2_EVENT 133 
#define  HWTSTAMP_FILTER_PTP_V2_L2_SYNC 132 
#define  HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ 131 
#define  HWTSTAMP_FILTER_PTP_V2_L4_EVENT 130 
#define  HWTSTAMP_FILTER_PTP_V2_L4_SYNC 129 
#define  HWTSTAMP_FILTER_PTP_V2_SYNC 128 
 scalar_t__ HWTSTAMP_TX_ONESTEP_SYNC ; 
 int /*<<< orphan*/  PAGE5 ; 
 int PTP_CLASS_L2 ; 
 int PTP_CLASS_L4 ; 
 int PTP_CLASS_V1 ; 
 void* PTP_CLASS_V2 ; 
 int /*<<< orphan*/  PTP_RXCFG0 ; 
 int /*<<< orphan*/  PTP_TXCFG0 ; 
 int RX_IPV4_EN ; 
 int RX_IPV6_EN ; 
 int RX_L2_EN ; 
 int RX_TS_EN ; 
 int SYNC_1STEP ; 
 int TX_IPV4_EN ; 
 int TX_IPV6_EN ; 
 int TX_L2_EN ; 
 int TX_PTP_VER_MASK ; 
 int TX_PTP_VER_SHIFT ; 
 int TX_TS_EN ; 
 scalar_t__ copy_from_user (struct hwtstamp_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 int /*<<< orphan*/  ext_write (int /*<<< orphan*/ ,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dp83640_hwtstamp(struct phy_device *phydev, struct ifreq *ifr)
{
	struct dp83640_private *dp83640 = phydev->priv;
	struct hwtstamp_config cfg;
	u16 txcfg0, rxcfg0;

	if (copy_from_user(&cfg, ifr->ifr_data, sizeof(cfg)))
		return -EFAULT;

	if (cfg.flags) /* reserved for future extensions */
		return -EINVAL;

	if (cfg.tx_type < 0 || cfg.tx_type > HWTSTAMP_TX_ONESTEP_SYNC)
		return -ERANGE;

	dp83640->hwts_tx_en = cfg.tx_type;

	switch (cfg.rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		dp83640->hwts_rx_en = 0;
		dp83640->layer = 0;
		dp83640->version = 0;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		dp83640->hwts_rx_en = 1;
		dp83640->layer = PTP_CLASS_L4;
		dp83640->version = PTP_CLASS_V1;
		break;
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		dp83640->hwts_rx_en = 1;
		dp83640->layer = PTP_CLASS_L4;
		dp83640->version = PTP_CLASS_V2;
		break;
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
		dp83640->hwts_rx_en = 1;
		dp83640->layer = PTP_CLASS_L2;
		dp83640->version = PTP_CLASS_V2;
		break;
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		dp83640->hwts_rx_en = 1;
		dp83640->layer = PTP_CLASS_L4 | PTP_CLASS_L2;
		dp83640->version = PTP_CLASS_V2;
		break;
	default:
		return -ERANGE;
	}

	txcfg0 = (dp83640->version & TX_PTP_VER_MASK) << TX_PTP_VER_SHIFT;
	rxcfg0 = (dp83640->version & TX_PTP_VER_MASK) << TX_PTP_VER_SHIFT;

	if (dp83640->layer & PTP_CLASS_L2) {
		txcfg0 |= TX_L2_EN;
		rxcfg0 |= RX_L2_EN;
	}
	if (dp83640->layer & PTP_CLASS_L4) {
		txcfg0 |= TX_IPV6_EN | TX_IPV4_EN;
		rxcfg0 |= RX_IPV6_EN | RX_IPV4_EN;
	}

	if (dp83640->hwts_tx_en)
		txcfg0 |= TX_TS_EN;

	if (dp83640->hwts_tx_en == HWTSTAMP_TX_ONESTEP_SYNC)
		txcfg0 |= SYNC_1STEP | CHK_1STEP;

	if (dp83640->hwts_rx_en)
		rxcfg0 |= RX_TS_EN;

	mutex_lock(&dp83640->clock->extreg_lock);

	ext_write(0, phydev, PAGE5, PTP_TXCFG0, txcfg0);
	ext_write(0, phydev, PAGE5, PTP_RXCFG0, rxcfg0);

	mutex_unlock(&dp83640->clock->extreg_lock);

	return copy_to_user(ifr->ifr_data, &cfg, sizeof(cfg)) ? -EFAULT : 0;
}