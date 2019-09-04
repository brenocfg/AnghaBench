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
struct super_block {int dummy; } ;
struct fid {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*) ; 

__attribute__((used)) static struct dentry *ovl_fh_to_parent(struct super_block *sb, struct fid *fid,
				       int fh_len, int fh_type)
{
	pr_warn_ratelimited("overlayfs: connectable file handles not supported; use 'no_subtree_check' exportfs option.\n");
	return ERR_PTR(-EACCES);
}