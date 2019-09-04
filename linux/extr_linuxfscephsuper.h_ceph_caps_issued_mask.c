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
struct ceph_inode_info {int /*<<< orphan*/  i_ceph_lock; } ;

/* Variables and functions */
 int __ceph_caps_issued_mask (struct ceph_inode_info*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ceph_caps_issued_mask(struct ceph_inode_info *ci, int mask,
					int touch)
{
	int r;
	spin_lock(&ci->i_ceph_lock);
	r = __ceph_caps_issued_mask(ci, mask, touch);
	spin_unlock(&ci->i_ceph_lock);
	return r;
}