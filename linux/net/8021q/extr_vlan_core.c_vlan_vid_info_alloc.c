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
struct vlan_vid_info {int /*<<< orphan*/  vid; int /*<<< orphan*/  proto; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vlan_vid_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vlan_vid_info *vlan_vid_info_alloc(__be16 proto, u16 vid)
{
	struct vlan_vid_info *vid_info;

	vid_info = kzalloc(sizeof(struct vlan_vid_info), GFP_KERNEL);
	if (!vid_info)
		return NULL;
	vid_info->proto = proto;
	vid_info->vid = vid;

	return vid_info;
}