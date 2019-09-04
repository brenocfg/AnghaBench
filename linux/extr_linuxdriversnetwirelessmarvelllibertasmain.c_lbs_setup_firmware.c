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
struct lbs_private {void* txpower_max; void* txpower_min; void* txpower_cur; int /*<<< orphan*/  current_addr; } ;
typedef  void* s16 ;

/* Variables and functions */
 int /*<<< orphan*/  SNMP_MIB_OID_11D_ENABLE ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int lbs_get_tx_power (struct lbs_private*,void**,void**,void**) ; 
 int lbs_set_mac_control_sync (struct lbs_private*) ; 
 int lbs_set_snmp_mib (struct lbs_private*,int /*<<< orphan*/ ,int) ; 
 int lbs_update_hw_spec (struct lbs_private*) ; 

__attribute__((used)) static int lbs_setup_firmware(struct lbs_private *priv)
{
	int ret = -1;
	s16 curlevel = 0, minlevel = 0, maxlevel = 0;

	/* Read MAC address from firmware */
	eth_broadcast_addr(priv->current_addr);
	ret = lbs_update_hw_spec(priv);
	if (ret)
		goto done;

	/* Read power levels if available */
	ret = lbs_get_tx_power(priv, &curlevel, &minlevel, &maxlevel);
	if (ret == 0) {
		priv->txpower_cur = curlevel;
		priv->txpower_min = minlevel;
		priv->txpower_max = maxlevel;
	}

	/* Send cmd to FW to enable 11D function */
	ret = lbs_set_snmp_mib(priv, SNMP_MIB_OID_11D_ENABLE, 1);
	if (ret)
		goto done;

	ret = lbs_set_mac_control_sync(priv);
done:
	return ret;
}