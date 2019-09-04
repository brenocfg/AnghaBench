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
typedef  void* u32 ;
struct rxf_desc {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int rx_coalesce_usecs; int tx_coalesce_usecs; int rx_max_coalesced_frames; int tx_max_coalesced_frames; } ;
struct bdx_priv {void* tdintcm; void* rdintcm; } ;

/* Variables and functions */
 int BDX_TXF_DESC_SZ ; 
 int EINVAL ; 
 int /*<<< orphan*/  GET_INT_COAL_RC (void*) ; 
 int /*<<< orphan*/  GET_RXF_TH (void*) ; 
 int INT_COAL_MULT ; 
 void* INT_REG_VAL (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int PCK_TH_MULT ; 
 int /*<<< orphan*/  WRITE_REG (struct bdx_priv*,int /*<<< orphan*/ ,void*) ; 
 struct bdx_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  regRDINTCM0 ; 
 int /*<<< orphan*/  regTDINTCM0 ; 

__attribute__((used)) static int
bdx_set_coalesce(struct net_device *netdev, struct ethtool_coalesce *ecoal)
{
	u32 rdintcm;
	u32 tdintcm;
	struct bdx_priv *priv = netdev_priv(netdev);
	int rx_coal;
	int tx_coal;
	int rx_max_coal;
	int tx_max_coal;

	/* Check for valid input */
	rx_coal = ecoal->rx_coalesce_usecs / INT_COAL_MULT;
	tx_coal = ecoal->tx_coalesce_usecs / INT_COAL_MULT;
	rx_max_coal = ecoal->rx_max_coalesced_frames;
	tx_max_coal = ecoal->tx_max_coalesced_frames;

	/* Translate from packets to multiples of FIFO bytes */
	rx_max_coal =
	    (((rx_max_coal * sizeof(struct rxf_desc)) + PCK_TH_MULT - 1)
	     / PCK_TH_MULT);
	tx_max_coal =
	    (((tx_max_coal * BDX_TXF_DESC_SZ) + PCK_TH_MULT - 1)
	     / PCK_TH_MULT);

	if ((rx_coal > 0x7FFF) || (tx_coal > 0x7FFF) ||
	    (rx_max_coal > 0xF) || (tx_max_coal > 0xF))
		return -EINVAL;

	rdintcm = INT_REG_VAL(rx_coal, GET_INT_COAL_RC(priv->rdintcm),
			      GET_RXF_TH(priv->rdintcm), rx_max_coal);
	tdintcm = INT_REG_VAL(tx_coal, GET_INT_COAL_RC(priv->tdintcm), 0,
			      tx_max_coal);

	priv->rdintcm = rdintcm;
	priv->tdintcm = tdintcm;

	WRITE_REG(priv, regRDINTCM0, rdintcm);
	WRITE_REG(priv, regTDINTCM0, tdintcm);

	return 0;
}