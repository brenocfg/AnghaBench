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
struct net_device {int /*<<< orphan*/  todo_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_unreg_count; } ;

/* Variables and functions */
 TYPE_1__* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_todo_list ; 

__attribute__((used)) static void net_set_todo(struct net_device *dev)
{
	list_add_tail(&dev->todo_list, &net_todo_list);
	dev_net(dev)->dev_unreg_count++;
}