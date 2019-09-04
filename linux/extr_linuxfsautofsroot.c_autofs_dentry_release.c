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
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct autofs_sb_info {int /*<<< orphan*/  lookup_lock; } ;
struct autofs_info {int /*<<< orphan*/  expiring; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 struct autofs_info* autofs_dentry_ino (struct dentry*) ; 
 int /*<<< orphan*/  autofs_free_ino (struct autofs_info*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void autofs_dentry_release(struct dentry *de)
{
	struct autofs_info *ino = autofs_dentry_ino(de);
	struct autofs_sb_info *sbi = autofs_sbi(de->d_sb);

	pr_debug("releasing %p\n", de);

	if (!ino)
		return;

	if (sbi) {
		spin_lock(&sbi->lookup_lock);
		if (!list_empty(&ino->active))
			list_del(&ino->active);
		if (!list_empty(&ino->expiring))
			list_del(&ino->expiring);
		spin_unlock(&sbi->lookup_lock);
	}

	autofs_free_ino(ino);
}