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
struct mount {int /*<<< orphan*/  mnt; } ;

/* Variables and functions */
 unsigned int MNT_READONLY ; 
 int __mnt_is_readonly (int /*<<< orphan*/ *) ; 
 int __mnt_unmake_readonly (struct mount*) ; 
 int mnt_make_readonly (struct mount*) ; 

__attribute__((used)) static int change_mount_ro_state(struct mount *mnt, unsigned int mnt_flags)
{
	bool readonly_request = (mnt_flags & MNT_READONLY);

	if (readonly_request == __mnt_is_readonly(&mnt->mnt))
		return 0;

	if (readonly_request)
		return mnt_make_readonly(mnt);

	return __mnt_unmake_readonly(mnt);
}