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
struct dentry {int /*<<< orphan*/  d_lock; struct dentry* d_parent; int /*<<< orphan*/  d_sb; } ;
struct autofs_sb_info {int /*<<< orphan*/  lookup_lock; } ;

/* Variables and functions */
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 struct dentry* dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* positive_after (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *get_next_positive_dentry(struct dentry *prev,
					       struct dentry *root)
{
	struct autofs_sb_info *sbi = autofs_sbi(root->d_sb);
	struct dentry *p = prev, *ret = NULL, *d = NULL;

	if (prev == NULL)
		return dget(root);

	spin_lock(&sbi->lookup_lock);
	spin_lock(&p->d_lock);
	while (1) {
		struct dentry *parent;

		ret = positive_after(p, d);
		if (ret || p == root)
			break;
		parent = p->d_parent;
		spin_unlock(&p->d_lock);
		spin_lock(&parent->d_lock);
		d = p;
		p = parent;
	}
	spin_unlock(&p->d_lock);
	spin_unlock(&sbi->lookup_lock);
	dput(prev);
	return ret;
}