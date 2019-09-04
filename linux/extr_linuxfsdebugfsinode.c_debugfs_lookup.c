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
struct dentry {int dummy; } ;
struct TYPE_2__ {struct dentry* mnt_root; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  d_really_is_positive (struct dentry*) ; 
 TYPE_1__* debugfs_mount ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct dentry* lookup_one_len_unlocked (char const*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

struct dentry *debugfs_lookup(const char *name, struct dentry *parent)
{
	struct dentry *dentry;

	if (IS_ERR(parent))
		return NULL;

	if (!parent)
		parent = debugfs_mount->mnt_root;

	dentry = lookup_one_len_unlocked(name, parent, strlen(name));
	if (IS_ERR(dentry))
		return NULL;
	if (!d_really_is_positive(dentry)) {
		dput(dentry);
		return NULL;
	}
	return dentry;
}