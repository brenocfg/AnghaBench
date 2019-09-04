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
struct ocfs2_super {int dummy; } ;
struct ocfs2_lock_res {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 int __ocfs2_cluster_lock (struct ocfs2_super*,struct ocfs2_lock_res*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ocfs2_cluster_lock(struct ocfs2_super *osb,
				     struct ocfs2_lock_res *lockres,
				     int level,
				     u32 lkm_flags,
				     int arg_flags)
{
	return __ocfs2_cluster_lock(osb, lockres, level, lkm_flags, arg_flags,
				    0, _RET_IP_);
}