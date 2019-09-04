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
struct ceph_inode_info {int /*<<< orphan*/  i_ordered_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __ceph_dir_clear_ordered(struct ceph_inode_info *ci)
{
	atomic64_inc(&ci->i_ordered_count);
}