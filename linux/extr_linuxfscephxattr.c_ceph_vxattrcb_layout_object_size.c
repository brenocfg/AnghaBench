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
struct TYPE_2__ {int object_size; } ;
struct ceph_inode_info {TYPE_1__ i_layout; } ;

/* Variables and functions */
 size_t snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static size_t ceph_vxattrcb_layout_object_size(struct ceph_inode_info *ci,
					       char *val, size_t size)
{
	return snprintf(val, size, "%u", ci->i_layout.object_size);
}