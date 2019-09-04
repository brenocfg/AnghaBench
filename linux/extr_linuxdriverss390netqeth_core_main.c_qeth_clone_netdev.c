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
struct net_device {int /*<<< orphan*/  dev_port; int /*<<< orphan*/  ml_priv; } ;

/* Variables and functions */
 struct net_device* qeth_alloc_netdev (int /*<<< orphan*/ ) ; 

struct net_device *qeth_clone_netdev(struct net_device *orig)
{
	struct net_device *clone = qeth_alloc_netdev(orig->ml_priv);

	if (!clone)
		return NULL;

	clone->dev_port = orig->dev_port;
	return clone;
}