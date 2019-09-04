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
struct TYPE_2__ {scalar_t__ length; } ;
union iwreq_data {TYPE_1__ data; } ;
struct net_device {int dummy; } ;
struct libipw_device {scalar_t__ wpa_ie_len; int /*<<< orphan*/ * wpa_ie; } ;
struct iw_request_info {int dummy; } ;
struct ipw_priv {struct libipw_device* ieee; } ;

/* Variables and functions */
 int E2BIG ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int ipw_wx_get_genie(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
	struct libipw_device *ieee = priv->ieee;
	int err = 0;

	if (ieee->wpa_ie_len == 0 || ieee->wpa_ie == NULL) {
		wrqu->data.length = 0;
		goto out;
	}

	if (wrqu->data.length < ieee->wpa_ie_len) {
		err = -E2BIG;
		goto out;
	}

	wrqu->data.length = ieee->wpa_ie_len;
	memcpy(extra, ieee->wpa_ie, ieee->wpa_ie_len);

      out:
	return err;
}