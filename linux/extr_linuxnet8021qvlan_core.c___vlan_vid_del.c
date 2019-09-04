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
typedef  int /*<<< orphan*/  u16 ;
struct vlan_vid_info {int /*<<< orphan*/  list; int /*<<< orphan*/  vid; int /*<<< orphan*/  proto; } ;
struct vlan_info {int /*<<< orphan*/  nr_vids; struct net_device* real_dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vlan_vid_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vlan_kill_rx_filter_info (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __vlan_vid_del(struct vlan_info *vlan_info,
			   struct vlan_vid_info *vid_info)
{
	struct net_device *dev = vlan_info->real_dev;
	__be16 proto = vid_info->proto;
	u16 vid = vid_info->vid;
	int err;

	err = vlan_kill_rx_filter_info(dev, proto, vid);
	if (err)
		pr_warn("failed to kill vid %04x/%d for device %s\n",
			proto, vid, dev->name);

	list_del(&vid_info->list);
	kfree(vid_info);
	vlan_info->nr_vids--;
}