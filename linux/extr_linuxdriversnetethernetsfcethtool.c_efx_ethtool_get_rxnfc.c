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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int flow_type; } ;
struct ethtool_rxnfc {int cmd; int data; int flow_type; int rule_cnt; int /*<<< orphan*/  rss_context; TYPE_1__ fs; } ;
struct efx_rss_context {int /*<<< orphan*/  rx_hash_udp_4tuple; } ;
struct efx_nic {int n_rx_channels; int /*<<< orphan*/  rss_lock; struct efx_rss_context rss_context; } ;
typedef  int s32 ;

/* Variables and functions */
#define  AH_ESP_V4_FLOW 142 
#define  AH_ESP_V6_FLOW 141 
 int /*<<< orphan*/  EFX_FILTER_PRI_MANUAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXCLSRLALL 140 
#define  ETHTOOL_GRXCLSRLCNT 139 
#define  ETHTOOL_GRXCLSRULE 138 
#define  ETHTOOL_GRXFH 137 
#define  ETHTOOL_GRXRINGS 136 
 int FLOW_RSS ; 
#define  IPV4_FLOW 135 
#define  IPV6_FLOW 134 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
 int RX_CLS_LOC_SPECIAL ; 
#define  SCTP_V4_FLOW 133 
#define  SCTP_V6_FLOW 132 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 int efx_ethtool_get_class_rule (struct efx_nic*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int efx_filter_count_rx_used (struct efx_nic*,int /*<<< orphan*/ ) ; 
 void* efx_filter_get_rx_id_limit (struct efx_nic*) ; 
 int efx_filter_get_rx_ids (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct efx_rss_context* efx_find_rss_context_entry (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_rss_active (struct efx_rss_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
efx_ethtool_get_rxnfc(struct net_device *net_dev,
		      struct ethtool_rxnfc *info, u32 *rule_locs)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	u32 rss_context = 0;
	s32 rc = 0;

	switch (info->cmd) {
	case ETHTOOL_GRXRINGS:
		info->data = efx->n_rx_channels;
		return 0;

	case ETHTOOL_GRXFH: {
		struct efx_rss_context *ctx = &efx->rss_context;

		mutex_lock(&efx->rss_lock);
		if (info->flow_type & FLOW_RSS && info->rss_context) {
			ctx = efx_find_rss_context_entry(efx, info->rss_context);
			if (!ctx) {
				rc = -ENOENT;
				goto out_unlock;
			}
		}
		info->data = 0;
		if (!efx_rss_active(ctx)) /* No RSS */
			goto out_unlock;
		switch (info->flow_type & ~FLOW_RSS) {
		case UDP_V4_FLOW:
			if (ctx->rx_hash_udp_4tuple)
				/* fall through */
		case TCP_V4_FLOW:
				info->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
			/* fall through */
		case SCTP_V4_FLOW:
		case AH_ESP_V4_FLOW:
		case IPV4_FLOW:
			info->data |= RXH_IP_SRC | RXH_IP_DST;
			break;
		case UDP_V6_FLOW:
			if (ctx->rx_hash_udp_4tuple)
				/* fall through */
		case TCP_V6_FLOW:
				info->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
			/* fall through */
		case SCTP_V6_FLOW:
		case AH_ESP_V6_FLOW:
		case IPV6_FLOW:
			info->data |= RXH_IP_SRC | RXH_IP_DST;
			break;
		default:
			break;
		}
out_unlock:
		mutex_unlock(&efx->rss_lock);
		return rc;
	}

	case ETHTOOL_GRXCLSRLCNT:
		info->data = efx_filter_get_rx_id_limit(efx);
		if (info->data == 0)
			return -EOPNOTSUPP;
		info->data |= RX_CLS_LOC_SPECIAL;
		info->rule_cnt =
			efx_filter_count_rx_used(efx, EFX_FILTER_PRI_MANUAL);
		return 0;

	case ETHTOOL_GRXCLSRULE:
		if (efx_filter_get_rx_id_limit(efx) == 0)
			return -EOPNOTSUPP;
		rc = efx_ethtool_get_class_rule(efx, &info->fs, &rss_context);
		if (rc < 0)
			return rc;
		if (info->fs.flow_type & FLOW_RSS)
			info->rss_context = rss_context;
		return 0;

	case ETHTOOL_GRXCLSRLALL:
		info->data = efx_filter_get_rx_id_limit(efx);
		if (info->data == 0)
			return -EOPNOTSUPP;
		rc = efx_filter_get_rx_ids(efx, EFX_FILTER_PRI_MANUAL,
					   rule_locs, info->rule_cnt);
		if (rc < 0)
			return rc;
		info->rule_cnt = rc;
		return 0;

	default:
		return -EOPNOTSUPP;
	}
}