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
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_sb; } ;
struct autofs_sb_info {int /*<<< orphan*/  lookup_lock; } ;

/* Variables and functions */
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* positive_after (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *get_next_positive_subdir(struct dentry *prev,
					       struct dentry *root)
{
	struct autofs_sb_info *sbi = autofs_sbi(root->d_sb);
	struct dentry *q;

	spin_lock(&sbi->lookup_lock);
	spin_lock(&root->d_lock);
	q = positive_after(root, prev);
	spin_unlock(&root->d_lock);
	spin_unlock(&sbi->lookup_lock);
	dput(prev);
	return q;
}