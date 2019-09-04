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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct wilc_vif {int /*<<< orphan*/  ndev; } ;
struct wilc_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ GO_NEG_REQ ; 
 scalar_t__ GO_NEG_RSP ; 
 scalar_t__ P2PELEM_ATTR_ID ; 
 scalar_t__ P2P_INV_REQ ; 
 scalar_t__ P2P_INV_RSP ; 
 size_t P2P_PUB_ACTION_SUBTYPE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ p2p_local_random ; 
 int /*<<< orphan*/  p2p_oui ; 
 scalar_t__ p2p_recv_random ; 
 int /*<<< orphan*/  p2p_vendor_spec ; 
 int wilc_ie ; 
 int /*<<< orphan*/  wilc_wfi_cfg_parse_rx_action (scalar_t__*,int) ; 

__attribute__((used)) static void wilc_wfi_cfg_parse_rx_vendor_spec(struct wilc_priv *priv, u8 *buff,
					      u32 size)
{
	int i;
	u8 subtype;
	struct wilc_vif *vif = netdev_priv(priv->dev);

	subtype = buff[P2P_PUB_ACTION_SUBTYPE];
	if ((subtype == GO_NEG_REQ || subtype == GO_NEG_RSP) && !wilc_ie) {
		for (i = P2P_PUB_ACTION_SUBTYPE; i < size; i++) {
			if (!memcmp(p2p_vendor_spec, &buff[i], 6)) {
				p2p_recv_random = buff[i + 6];
				wilc_ie = true;
				break;
			}
		}
	}

	if (p2p_local_random <= p2p_recv_random) {
		netdev_dbg(vif->ndev,
			   "PEER WILL BE GO LocaRand=%02x RecvRand %02x\n",
			   p2p_local_random, p2p_recv_random);
		return;
	}

	if (subtype == GO_NEG_REQ || subtype == GO_NEG_RSP ||
	    subtype == P2P_INV_REQ || subtype == P2P_INV_RSP) {
		for (i = P2P_PUB_ACTION_SUBTYPE + 2; i < size; i++) {
			if (buff[i] == P2PELEM_ATTR_ID &&
			    !(memcmp(p2p_oui, &buff[i + 2], 4))) {
				wilc_wfi_cfg_parse_rx_action(&buff[i + 6],
							     size - (i + 6));
				break;
			}
		}
	}
}