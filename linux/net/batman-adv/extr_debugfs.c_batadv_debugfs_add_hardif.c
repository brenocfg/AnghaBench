#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net {int dummy; } ;
struct batadv_hard_iface {TYPE_2__* net_dev; int /*<<< orphan*/  debug_dir; } ;
struct TYPE_4__ {int mode; int /*<<< orphan*/  name; } ;
struct batadv_debuginfo {int /*<<< orphan*/  fops; TYPE_1__ attr; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int S_IFREG ; 
 int /*<<< orphan*/  batadv_debugfs ; 
 struct batadv_debuginfo** batadv_hardif_debuginfos ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 struct net* dev_net (TYPE_2__*) ; 
 struct net init_net ; 

void batadv_debugfs_add_hardif(struct batadv_hard_iface *hard_iface)
{
	struct net *net = dev_net(hard_iface->net_dev);
	struct batadv_debuginfo **bat_debug;

	if (net != &init_net)
		return;

	hard_iface->debug_dir = debugfs_create_dir(hard_iface->net_dev->name,
						   batadv_debugfs);

	for (bat_debug = batadv_hardif_debuginfos; *bat_debug; ++bat_debug)
		debugfs_create_file(((*bat_debug)->attr).name,
				    S_IFREG | ((*bat_debug)->attr).mode,
				    hard_iface->debug_dir, hard_iface->net_dev,
				    &(*bat_debug)->fops);
}