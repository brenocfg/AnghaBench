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
struct gprs_dev {int /*<<< orphan*/  sk; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ pep_writeable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gprs_writeable(struct gprs_dev *gp)
{
	struct net_device *dev = gp->dev;

	if (pep_writeable(gp->sk))
		netif_wake_queue(dev);
}