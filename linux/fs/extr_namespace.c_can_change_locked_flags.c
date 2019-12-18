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
struct TYPE_2__ {unsigned int mnt_flags; } ;
struct mount {TYPE_1__ mnt; } ;

/* Variables and functions */
 unsigned int MNT_ATIME_MASK ; 
 unsigned int MNT_LOCK_ATIME ; 
 unsigned int MNT_LOCK_NODEV ; 
 unsigned int MNT_LOCK_NOEXEC ; 
 unsigned int MNT_LOCK_NOSUID ; 
 unsigned int MNT_LOCK_READONLY ; 
 unsigned int MNT_NODEV ; 
 unsigned int MNT_NOEXEC ; 
 unsigned int MNT_NOSUID ; 
 unsigned int MNT_READONLY ; 

__attribute__((used)) static bool can_change_locked_flags(struct mount *mnt, unsigned int mnt_flags)
{
	unsigned int fl = mnt->mnt.mnt_flags;

	if ((fl & MNT_LOCK_READONLY) &&
	    !(mnt_flags & MNT_READONLY))
		return false;

	if ((fl & MNT_LOCK_NODEV) &&
	    !(mnt_flags & MNT_NODEV))
		return false;

	if ((fl & MNT_LOCK_NOSUID) &&
	    !(mnt_flags & MNT_NOSUID))
		return false;

	if ((fl & MNT_LOCK_NOEXEC) &&
	    !(mnt_flags & MNT_NOEXEC))
		return false;

	if ((fl & MNT_LOCK_ATIME) &&
	    ((fl & MNT_ATIME_MASK) != (mnt_flags & MNT_ATIME_MASK)))
		return false;

	return true;
}