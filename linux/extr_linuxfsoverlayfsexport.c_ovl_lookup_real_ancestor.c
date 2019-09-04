#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {struct dentry* s_root; } ;
struct ovl_layer {TYPE_1__* mnt; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct dentry* mnt_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXDEV ; 
 struct dentry* dget (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* ovl_lookup_real_inode (struct super_block*,struct dentry*,struct ovl_layer*) ; 

__attribute__((used)) static struct dentry *ovl_lookup_real_ancestor(struct super_block *sb,
					       struct dentry *real,
					       struct ovl_layer *layer)
{
	struct dentry *next, *parent = NULL;
	struct dentry *ancestor = ERR_PTR(-EIO);

	if (real == layer->mnt->mnt_root)
		return dget(sb->s_root);

	/* Find the topmost indexed or hashed ancestor */
	next = dget(real);
	for (;;) {
		parent = dget_parent(next);

		/*
		 * Lookup a matching overlay dentry in inode/dentry
		 * cache or in index by real inode.
		 */
		ancestor = ovl_lookup_real_inode(sb, next, layer);
		if (ancestor)
			break;

		if (parent == layer->mnt->mnt_root) {
			ancestor = dget(sb->s_root);
			break;
		}

		/*
		 * If @real has been moved out of the layer root directory,
		 * we will eventully hit the real fs root. This cannot happen
		 * by legit overlay rename, so we return error in that case.
		 */
		if (parent == next) {
			ancestor = ERR_PTR(-EXDEV);
			break;
		}

		dput(next);
		next = parent;
	}

	dput(parent);
	dput(next);

	return ancestor;
}