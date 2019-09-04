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
struct TYPE_2__ {scalar_t__ sa_family; int /*<<< orphan*/  sa_data; } ;
union iwreq_data {TYPE_1__ ap_addr; } ;
struct wl3501_card {int /*<<< orphan*/  bssid; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wl3501_card* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int wl3501_set_wap(struct net_device *dev, struct iw_request_info *info,
			  union iwreq_data *wrqu, char *extra)
{
	struct wl3501_card *this = netdev_priv(dev);
	int rc = -EINVAL;

	/* FIXME: we support other ARPHRDs...*/
	if (wrqu->ap_addr.sa_family != ARPHRD_ETHER)
		goto out;
	if (is_broadcast_ether_addr(wrqu->ap_addr.sa_data)) {
		/* FIXME: rescan? */
	} else
		memcpy(this->bssid, wrqu->ap_addr.sa_data, ETH_ALEN);
		/* FIXME: rescan? deassoc & scan? */
	rc = 0;
out:
	return rc;
}