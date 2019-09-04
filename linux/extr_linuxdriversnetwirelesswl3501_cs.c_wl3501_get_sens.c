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
struct TYPE_2__ {int disabled; int fixed; int /*<<< orphan*/  value; } ;
union iwreq_data {TYPE_1__ sens; } ;
struct wl3501_card {int /*<<< orphan*/  rssi; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 struct wl3501_card* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int wl3501_get_sens(struct net_device *dev, struct iw_request_info *info,
			   union iwreq_data *wrqu, char *extra)
{
	struct wl3501_card *this = netdev_priv(dev);

	wrqu->sens.value = this->rssi;
	wrqu->sens.disabled = !wrqu->sens.value;
	wrqu->sens.fixed = 1;
	return 0;
}