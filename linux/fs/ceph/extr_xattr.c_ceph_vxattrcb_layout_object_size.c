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
struct TYPE_2__ {int /*<<< orphan*/  object_size; } ;
struct ceph_inode_info {TYPE_1__ i_layout; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_fmt_xattr (char*,size_t,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ceph_vxattrcb_layout_object_size(struct ceph_inode_info *ci,
						char *val, size_t size)
{
	return ceph_fmt_xattr(val, size, "%u", ci->i_layout.object_size);
}