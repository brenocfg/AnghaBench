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
struct iw_freq {scalar_t__ e; int /*<<< orphan*/  m; } ;
struct atmel_private {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 struct atmel_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int atmel_get_freq(struct net_device *dev,
			  struct iw_request_info *info,
			  struct iw_freq *fwrq,
			  char *extra)
{
	struct atmel_private *priv = netdev_priv(dev);

	fwrq->m = priv->channel;
	fwrq->e = 0;
	return 0;
}