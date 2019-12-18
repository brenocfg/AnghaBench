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
struct ceph_inode_info {int /*<<< orphan*/  i_max_files; int /*<<< orphan*/  i_max_bytes; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_fmt_xattr (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ceph_vxattrcb_quota(struct ceph_inode_info *ci, char *val,
				   size_t size)
{
	return ceph_fmt_xattr(val, size, "max_bytes=%llu max_files=%llu",
				ci->i_max_bytes, ci->i_max_files);
}