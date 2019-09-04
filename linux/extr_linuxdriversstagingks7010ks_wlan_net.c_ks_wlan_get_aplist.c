#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int length; } ;
union iwreq_data {TYPE_3__ data; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; int /*<<< orphan*/  sa_data; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int size; TYPE_1__* ap; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; TYPE_2__ aplist; } ;
struct iw_request_info {int dummy; } ;
struct iw_quality {int updated; scalar_t__ noise; int /*<<< orphan*/  qual; scalar_t__ level; } ;
struct TYPE_4__ {int /*<<< orphan*/  sq; scalar_t__ rssi; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int EPERM ; 
 int LOCAL_APLIST_MAX ; 
 scalar_t__ SLP_SLEEP ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,struct iw_quality**,int) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_get_aplist(struct net_device *dev,
			      struct iw_request_info *info,
			      union iwreq_data *dwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);
	struct sockaddr *address = (struct sockaddr *)extra;
	struct iw_quality qual[LOCAL_APLIST_MAX];
	int i;

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;
	/* for SLEEP MODE */
	for (i = 0; i < priv->aplist.size; i++) {
		ether_addr_copy(address[i].sa_data, priv->aplist.ap[i].bssid);
		address[i].sa_family = ARPHRD_ETHER;
		qual[i].level = 256 - priv->aplist.ap[i].rssi;
		qual[i].qual = priv->aplist.ap[i].sq;
		qual[i].noise = 0;	/* invalid noise value */
		qual[i].updated = 7;
	}
	if (i) {
		dwrq->data.flags = 1;	/* Should be define'd */
		memcpy(extra + sizeof(struct sockaddr) * i,
		       &qual, sizeof(struct iw_quality) * i);
	}
	dwrq->data.length = i;

	return 0;
}