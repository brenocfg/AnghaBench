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
struct ocfs2_super {int dummy; } ;
struct ocfs2_lock_res {struct ocfs2_super* l_priv; } ;
struct ocfs2_refcount_tree {struct ocfs2_lock_res rf_lockres; } ;

/* Variables and functions */
 int DLM_LOCK_EX ; 
 int DLM_LOCK_PR ; 
 int /*<<< orphan*/  ocfs2_cluster_unlock (struct ocfs2_super*,struct ocfs2_lock_res*,int) ; 
 int /*<<< orphan*/  ocfs2_mount_local (struct ocfs2_super*) ; 

void ocfs2_refcount_unlock(struct ocfs2_refcount_tree *ref_tree, int ex)
{
	int level = ex ? DLM_LOCK_EX : DLM_LOCK_PR;
	struct ocfs2_lock_res *lockres = &ref_tree->rf_lockres;
	struct ocfs2_super *osb = lockres->l_priv;

	if (!ocfs2_mount_local(osb))
		ocfs2_cluster_unlock(osb, lockres, level);
}