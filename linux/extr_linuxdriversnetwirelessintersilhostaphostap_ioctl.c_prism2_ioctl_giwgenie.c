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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int length; } ;
struct hostap_interface {TYPE_1__* local; } ;
struct TYPE_2__ {int generic_elem_len; int /*<<< orphan*/ * generic_elem; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int E2BIG ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int prism2_ioctl_giwgenie(struct net_device *dev,
				 struct iw_request_info *info,
				 struct iw_point *data, char *extra)
{
	struct hostap_interface *iface = netdev_priv(dev);
	local_info_t *local = iface->local;
	int len = local->generic_elem_len - 2;

	if (len <= 0 || local->generic_elem == NULL) {
		data->length = 0;
		return 0;
	}

	if (data->length < len)
		return -E2BIG;

	data->length = len;
	memcpy(extra, local->generic_elem + 2, len);

	return 0;
}