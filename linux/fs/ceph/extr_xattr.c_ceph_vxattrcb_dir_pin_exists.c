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
struct ceph_inode_info {int /*<<< orphan*/  i_dir_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODATA ; 

__attribute__((used)) static bool ceph_vxattrcb_dir_pin_exists(struct ceph_inode_info *ci)
{
	return ci->i_dir_pin != -ENODATA;
}