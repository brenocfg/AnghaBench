#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_3__* mnt; } ;
typedef  int __u64 ;
struct TYPE_6__ {TYPE_2__* mnt_sb; } ;
struct TYPE_5__ {TYPE_1__* s_type; } ;
struct TYPE_4__ {int fs_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int FANOTIFY_PERM_EVENTS ; 
 int FS_DISALLOW_NOTIFY_PERM ; 

__attribute__((used)) static int fanotify_events_supported(struct path *path, __u64 mask)
{
	/*
	 * Some filesystems such as 'proc' acquire unusual locks when opening
	 * files. For them fanotify permission events have high chances of
	 * deadlocking the system - open done when reporting fanotify event
	 * blocks on this "unusual" lock while another process holding the lock
	 * waits for fanotify permission event to be answered. Just disallow
	 * permission events for such filesystems.
	 */
	if (mask & FANOTIFY_PERM_EVENTS &&
	    path->mnt->mnt_sb->s_type->fs_flags & FS_DISALLOW_NOTIFY_PERM)
		return -EINVAL;
	return 0;
}