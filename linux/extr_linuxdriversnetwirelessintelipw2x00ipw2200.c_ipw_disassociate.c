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
struct ipw_priv {int status; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int STATUS_ASSOCIATED ; 
 int STATUS_ASSOCIATING ; 
 int /*<<< orphan*/  ipw_send_disassociate (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipw_disassociate(void *data)
{
	struct ipw_priv *priv = data;
	if (!(priv->status & (STATUS_ASSOCIATED | STATUS_ASSOCIATING)))
		return 0;
	ipw_send_disassociate(data, 0);
	netif_carrier_off(priv->net_dev);
	return 1;
}