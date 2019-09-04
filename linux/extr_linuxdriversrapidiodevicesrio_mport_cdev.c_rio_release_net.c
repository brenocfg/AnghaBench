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
struct rio_net {int /*<<< orphan*/  id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDEV ; 
 int /*<<< orphan*/  kfree (struct rio_net*) ; 
 int /*<<< orphan*/  rmcd_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct rio_net* to_rio_net (struct device*) ; 

__attribute__((used)) static void rio_release_net(struct device *dev)
{
	struct rio_net *net;

	net = to_rio_net(dev);
	rmcd_debug(RDEV, "net_%d", net->id);
	kfree(net);
}