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
struct vlan_vid_info {int /*<<< orphan*/  list; } ;
struct vlan_info {int /*<<< orphan*/  nr_vids; int /*<<< orphan*/  vid_list; struct net_device* real_dev; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  kfree (struct vlan_vid_info*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vlan_add_rx_filter_info (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vlan_vid_info* vlan_vid_info_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __vlan_vid_add(struct vlan_info *vlan_info, __be16 proto, u16 vid,
			  struct vlan_vid_info **pvid_info)
{
	struct net_device *dev = vlan_info->real_dev;
	struct vlan_vid_info *vid_info;
	int err;

	vid_info = vlan_vid_info_alloc(proto, vid);
	if (!vid_info)
		return -ENOMEM;

	err = vlan_add_rx_filter_info(dev, proto, vid);
	if (err) {
		kfree(vid_info);
		return err;
	}

	list_add(&vid_info->list, &vlan_info->vid_list);
	vlan_info->nr_vids++;
	*pvid_info = vid_info;
	return 0;
}