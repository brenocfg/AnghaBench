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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int flags; int /*<<< orphan*/  length; } ;
struct atmel_private {int connect_to_any_BSS; int /*<<< orphan*/  new_SSID_size; int /*<<< orphan*/  new_SSID; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int IW_ENCODE_INDEX ; 
 int /*<<< orphan*/  MAX_SSID_LENGTH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct atmel_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atmel_set_essid(struct net_device *dev,
			   struct iw_request_info *info,
			   struct iw_point *dwrq,
			   char *extra)
{
	struct atmel_private *priv = netdev_priv(dev);

	/* Check if we asked for `any' */
	if (dwrq->flags == 0) {
		priv->connect_to_any_BSS = 1;
	} else {
		int index = (dwrq->flags & IW_ENCODE_INDEX) - 1;

		priv->connect_to_any_BSS = 0;

		/* Check the size of the string */
		if (dwrq->length > MAX_SSID_LENGTH)
			 return -E2BIG;
		if (index != 0)
			return -EINVAL;

		memcpy(priv->new_SSID, extra, dwrq->length);
		priv->new_SSID_size = dwrq->length;
	}

	return -EINPROGRESS;
}