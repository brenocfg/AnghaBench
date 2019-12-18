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
typedef  int /*<<< orphan*/  u32 ;
struct ceph_inode_info {int /*<<< orphan*/  i_fragtree_mutex; } ;
struct ceph_inode_frag {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ceph_choose_frag (struct ceph_inode_info*,int /*<<< orphan*/ ,struct ceph_inode_frag*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

u32 ceph_choose_frag(struct ceph_inode_info *ci, u32 v,
		     struct ceph_inode_frag *pfrag, int *found)
{
	u32 ret;
	mutex_lock(&ci->i_fragtree_mutex);
	ret = __ceph_choose_frag(ci, v, pfrag, found);
	mutex_unlock(&ci->i_fragtree_mutex);
	return ret;
}