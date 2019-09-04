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
struct path {scalar_t__ dentry; } ;
struct fs_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  seq; struct path root; } ;

/* Variables and functions */
 int /*<<< orphan*/  path_get (struct path const*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 

void set_fs_root(struct fs_struct *fs, const struct path *path)
{
	struct path old_root;

	path_get(path);
	spin_lock(&fs->lock);
	write_seqcount_begin(&fs->seq);
	old_root = fs->root;
	fs->root = *path;
	write_seqcount_end(&fs->seq);
	spin_unlock(&fs->lock);
	if (old_root.dentry)
		path_put(&old_root);
}