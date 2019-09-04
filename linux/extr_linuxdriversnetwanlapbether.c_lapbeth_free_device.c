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
struct lapbethdev {int /*<<< orphan*/  axdev; int /*<<< orphan*/  node; int /*<<< orphan*/  ethdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lapbeth_free_device(struct lapbethdev *lapbeth)
{
	dev_put(lapbeth->ethdev);
	list_del_rcu(&lapbeth->node);
	unregister_netdevice(lapbeth->axdev);
}