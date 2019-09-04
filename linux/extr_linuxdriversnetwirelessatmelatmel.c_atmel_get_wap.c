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
struct sockaddr {int /*<<< orphan*/  sa_family; int /*<<< orphan*/  sa_data; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct atmel_private {int /*<<< orphan*/  CurrentBSSID; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atmel_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atmel_get_wap(struct net_device *dev,
			 struct iw_request_info *info,
			 struct sockaddr *awrq,
			 char *extra)
{
	struct atmel_private *priv = netdev_priv(dev);
	memcpy(awrq->sa_data, priv->CurrentBSSID, ETH_ALEN);
	awrq->sa_family = ARPHRD_ETHER;

	return 0;
}