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
struct TYPE_4__ {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
struct TYPE_3__ {scalar_t__ flags; scalar_t__ length; } ;
union iwreq_data {TYPE_2__ ap_addr; TYPE_1__ data; } ;
struct net_device {int dummy; } ;
struct ks_wlan_private {unsigned int connect_status; scalar_t__ dev_state; scalar_t__ scan_ind_count; struct net_device* net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 scalar_t__ DEVICE_STATE_READY ; 
 scalar_t__ DEVICE_STATE_SLEEP ; 
 unsigned int DISCONNECT_STATUS ; 
 unsigned int FORCE_DISCONNECT ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 int /*<<< orphan*/  SME_STOP_CONFIRM ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostif_sme_enqueue (struct ks_wlan_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_connect_status (unsigned int) ; 
 scalar_t__ is_disconnect_status (unsigned int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  wireless_send_event (struct net_device*,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void hostif_stop_confirm(struct ks_wlan_private *priv)
{
	unsigned int tmp = 0;
	unsigned int old_status = priv->connect_status;
	struct net_device *netdev = priv->net_dev;
	union iwreq_data wrqu0;

	if (priv->dev_state == DEVICE_STATE_SLEEP)
		priv->dev_state = DEVICE_STATE_READY;

	/* disconnect indication */
	if (is_connect_status(priv->connect_status)) {
		netif_carrier_off(netdev);
		tmp = FORCE_DISCONNECT & priv->connect_status;
		priv->connect_status = tmp | DISCONNECT_STATUS;
		netdev_info(netdev, "IWEVENT: disconnect\n");

		wrqu0.data.length = 0;
		wrqu0.data.flags = 0;
		wrqu0.ap_addr.sa_family = ARPHRD_ETHER;
		if (is_disconnect_status(priv->connect_status) &&
		    is_connect_status(old_status)) {
			eth_zero_addr(wrqu0.ap_addr.sa_data);
			netdev_info(netdev, "IWEVENT: disconnect\n");
			wireless_send_event(netdev, SIOCGIWAP, &wrqu0, NULL);
		}
		priv->scan_ind_count = 0;
	}

	hostif_sme_enqueue(priv, SME_STOP_CONFIRM);
}