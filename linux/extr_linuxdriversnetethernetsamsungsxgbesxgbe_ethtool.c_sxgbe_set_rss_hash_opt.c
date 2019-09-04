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
typedef  int /*<<< orphan*/  u32 ;
struct sxgbe_priv_data {scalar_t__ ioaddr; } ;
struct ethtool_rxnfc {int data; int flow_type; } ;

/* Variables and functions */
#define  AH_ESP_V4_FLOW 141 
#define  AH_ESP_V6_FLOW 140 
#define  AH_V4_FLOW 139 
#define  AH_V6_FLOW 138 
 int EINVAL ; 
#define  ESP_V4_FLOW 137 
#define  ESP_V6_FLOW 136 
#define  IPV4_FLOW 135 
#define  IPV6_FLOW 134 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
#define  SCTP_V4_FLOW 133 
#define  SCTP_V6_FLOW 132 
 int /*<<< orphan*/  SXGBE_CORE_RSS_CTL_IP2TE ; 
 scalar_t__ SXGBE_CORE_RSS_CTL_REG ; 
 int /*<<< orphan*/  SXGBE_CORE_RSS_CTL_TCP4TE ; 
 int /*<<< orphan*/  SXGBE_CORE_RSS_CTL_UDP4TE ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sxgbe_set_rss_hash_opt(struct sxgbe_priv_data *priv,
				  struct ethtool_rxnfc *cmd)
{
	u32 reg_val = 0;

	/* RSS does not support anything other than hashing
	 * to queues on src and dst IPs and ports
	 */
	if (cmd->data & ~(RXH_IP_SRC | RXH_IP_DST |
			  RXH_L4_B_0_1 | RXH_L4_B_2_3))
		return -EINVAL;

	switch (cmd->flow_type) {
	case TCP_V4_FLOW:
	case TCP_V6_FLOW:
		if (!(cmd->data & RXH_IP_SRC) ||
		    !(cmd->data & RXH_IP_DST) ||
		    !(cmd->data & RXH_L4_B_0_1) ||
		    !(cmd->data & RXH_L4_B_2_3))
			return -EINVAL;
		reg_val = SXGBE_CORE_RSS_CTL_TCP4TE;
		break;
	case UDP_V4_FLOW:
	case UDP_V6_FLOW:
		if (!(cmd->data & RXH_IP_SRC) ||
		    !(cmd->data & RXH_IP_DST) ||
		    !(cmd->data & RXH_L4_B_0_1) ||
		    !(cmd->data & RXH_L4_B_2_3))
			return -EINVAL;
		reg_val = SXGBE_CORE_RSS_CTL_UDP4TE;
		break;
	case SCTP_V4_FLOW:
	case AH_ESP_V4_FLOW:
	case AH_V4_FLOW:
	case ESP_V4_FLOW:
	case AH_ESP_V6_FLOW:
	case AH_V6_FLOW:
	case ESP_V6_FLOW:
	case SCTP_V6_FLOW:
	case IPV4_FLOW:
	case IPV6_FLOW:
		if (!(cmd->data & RXH_IP_SRC) ||
		    !(cmd->data & RXH_IP_DST) ||
		    (cmd->data & RXH_L4_B_0_1) ||
		    (cmd->data & RXH_L4_B_2_3))
			return -EINVAL;
		reg_val = SXGBE_CORE_RSS_CTL_IP2TE;
		break;
	default:
		return -EINVAL;
	}

	/* Read SXGBE RSS control register and update */
	reg_val |= readl(priv->ioaddr + SXGBE_CORE_RSS_CTL_REG);
	writel(reg_val, priv->ioaddr + SXGBE_CORE_RSS_CTL_REG);
	readl(priv->ioaddr + SXGBE_CORE_RSS_CTL_REG);

	return 0;
}