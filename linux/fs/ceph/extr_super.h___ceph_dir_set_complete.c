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
struct ceph_inode_info {int /*<<< orphan*/ * i_complete_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,long long) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static inline void __ceph_dir_set_complete(struct ceph_inode_info *ci,
					   long long release_count,
					   long long ordered_count)
{
	/*
	 * Makes sure operations that setup readdir cache (update page
	 * cache and i_size) are strongly ordered w.r.t. the following
	 * atomic64_set() operations.
	 */
	smp_mb();
	atomic64_set(&ci->i_complete_seq[0], release_count);
	atomic64_set(&ci->i_complete_seq[1], ordered_count);
}