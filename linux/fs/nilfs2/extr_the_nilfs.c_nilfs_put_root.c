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
struct the_nilfs {int /*<<< orphan*/  ns_cptree_lock; int /*<<< orphan*/  ns_cptree; } ;
struct nilfs_root {int /*<<< orphan*/  ifile; int /*<<< orphan*/  rb_node; struct the_nilfs* nilfs; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nilfs_root*) ; 
 int /*<<< orphan*/  nilfs_sysfs_delete_snapshot_group (struct nilfs_root*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nilfs_put_root(struct nilfs_root *root)
{
	if (refcount_dec_and_test(&root->count)) {
		struct the_nilfs *nilfs = root->nilfs;

		nilfs_sysfs_delete_snapshot_group(root);

		spin_lock(&nilfs->ns_cptree_lock);
		rb_erase(&root->rb_node, &nilfs->ns_cptree);
		spin_unlock(&nilfs->ns_cptree_lock);
		iput(root->ifile);

		kfree(root);
	}
}