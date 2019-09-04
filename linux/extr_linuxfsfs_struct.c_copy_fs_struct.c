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
struct fs_struct {int users; int /*<<< orphan*/  lock; int /*<<< orphan*/  pwd; int /*<<< orphan*/  root; int /*<<< orphan*/  umask; int /*<<< orphan*/  seq; scalar_t__ in_exec; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fs_cachep ; 
 struct fs_struct* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seqcount_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct fs_struct *copy_fs_struct(struct fs_struct *old)
{
	struct fs_struct *fs = kmem_cache_alloc(fs_cachep, GFP_KERNEL);
	/* We don't need to lock fs - think why ;-) */
	if (fs) {
		fs->users = 1;
		fs->in_exec = 0;
		spin_lock_init(&fs->lock);
		seqcount_init(&fs->seq);
		fs->umask = old->umask;

		spin_lock(&old->lock);
		fs->root = old->root;
		path_get(&fs->root);
		fs->pwd = old->pwd;
		path_get(&fs->pwd);
		spin_unlock(&old->lock);
	}
	return fs;
}