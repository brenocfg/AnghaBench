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
typedef  int u32 ;
struct ipw_priv {int status; scalar_t__ tx_packets; } ;
typedef  int /*<<< orphan*/  rate ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IPW_ORD_STAT_TX_CURR_RATE ; 
 scalar_t__ IPW_REAL_RATE_RX_PACKET_THRESHOLD ; 
#define  IPW_TX_RATE_11MB 139 
#define  IPW_TX_RATE_12MB 138 
#define  IPW_TX_RATE_18MB 137 
#define  IPW_TX_RATE_1MB 136 
#define  IPW_TX_RATE_24MB 135 
#define  IPW_TX_RATE_2MB 134 
#define  IPW_TX_RATE_36MB 133 
#define  IPW_TX_RATE_48MB 132 
#define  IPW_TX_RATE_54MB 131 
#define  IPW_TX_RATE_5MB 130 
#define  IPW_TX_RATE_6MB 129 
#define  IPW_TX_RATE_9MB 128 
 int STATUS_ASSOCIATED ; 
 int ipw_get_max_rate (struct ipw_priv*) ; 
 int ipw_get_ordinal (struct ipw_priv*,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static u32 ipw_get_current_rate(struct ipw_priv *priv)
{
	u32 rate, len = sizeof(rate);
	int err;

	if (!(priv->status & STATUS_ASSOCIATED))
		return 0;

	if (priv->tx_packets > IPW_REAL_RATE_RX_PACKET_THRESHOLD) {
		err = ipw_get_ordinal(priv, IPW_ORD_STAT_TX_CURR_RATE, &rate,
				      &len);
		if (err) {
			IPW_DEBUG_INFO("failed querying ordinals.\n");
			return 0;
		}
	} else
		return ipw_get_max_rate(priv);

	switch (rate) {
	case IPW_TX_RATE_1MB:
		return 1000000;
	case IPW_TX_RATE_2MB:
		return 2000000;
	case IPW_TX_RATE_5MB:
		return 5500000;
	case IPW_TX_RATE_6MB:
		return 6000000;
	case IPW_TX_RATE_9MB:
		return 9000000;
	case IPW_TX_RATE_11MB:
		return 11000000;
	case IPW_TX_RATE_12MB:
		return 12000000;
	case IPW_TX_RATE_18MB:
		return 18000000;
	case IPW_TX_RATE_24MB:
		return 24000000;
	case IPW_TX_RATE_36MB:
		return 36000000;
	case IPW_TX_RATE_48MB:
		return 48000000;
	case IPW_TX_RATE_54MB:
		return 54000000;
	}

	return 0;
}