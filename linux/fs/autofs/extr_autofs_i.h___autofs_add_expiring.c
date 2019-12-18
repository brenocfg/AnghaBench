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
struct autofs_sb_info {int /*<<< orphan*/  expiring_list; } ;
struct autofs_info {int /*<<< orphan*/  expiring; } ;

/* Variables and functions */
 struct autofs_info* autofs_dentry_ino (struct dentry*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __autofs_add_expiring(struct dentry *dentry)
{
	struct autofs_sb_info *sbi = autofs_sbi(dentry->d_sb);
	struct autofs_info *ino = autofs_dentry_ino(dentry);

	if (ino) {
		if (list_empty(&ino->expiring))
			list_add(&ino->expiring, &sbi->expiring_list);
	}
}