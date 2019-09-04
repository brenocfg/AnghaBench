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
struct TYPE_5__ {int m; int e; } ;
union iwreq_data {TYPE_2__ freq; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ channel; } ;
struct TYPE_6__ {scalar_t__ channel; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; TYPE_1__ reg; TYPE_3__ current_ap; int /*<<< orphan*/  connect_status; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ SLP_SLEEP ; 
 int* frequency_list ; 
 scalar_t__ is_connect_status (int /*<<< orphan*/ ) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ks_wlan_get_freq(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *fwrq, char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);
	int f;

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	/* for SLEEP MODE */
	if (is_connect_status(priv->connect_status))
		f = (int)priv->current_ap.channel;
	else
		f = (int)priv->reg.channel;

	fwrq->freq.m = frequency_list[f - 1] * 100000;
	fwrq->freq.e = 1;

	return 0;
}