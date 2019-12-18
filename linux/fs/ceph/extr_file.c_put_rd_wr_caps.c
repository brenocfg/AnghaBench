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
struct ceph_inode_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_put_cap_refs (struct ceph_inode_info*,int) ; 

__attribute__((used)) static void put_rd_wr_caps(struct ceph_inode_info *src_ci, int src_got,
			   struct ceph_inode_info *dst_ci, int dst_got)
{
	ceph_put_cap_refs(src_ci, src_got);
	ceph_put_cap_refs(dst_ci, dst_got);
}