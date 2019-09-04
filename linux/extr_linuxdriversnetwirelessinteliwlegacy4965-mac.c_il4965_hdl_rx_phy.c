#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct il_rx_pkt {TYPE_2__ u; } ;
struct il_rx_phy_res {int dummy; } ;
struct il_rx_buf {int dummy; } ;
struct TYPE_3__ {int last_phy_res_valid; int /*<<< orphan*/  last_phy_res; int /*<<< orphan*/  ampdu_ref; } ;
struct il_priv {TYPE_1__ _4965; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 

__attribute__((used)) static void
il4965_hdl_rx_phy(struct il_priv *il, struct il_rx_buf *rxb)
{
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	il->_4965.last_phy_res_valid = true;
	il->_4965.ampdu_ref++;
	memcpy(&il->_4965.last_phy_res, pkt->u.raw,
	       sizeof(struct il_rx_phy_res));
}