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
struct vfsmount {int dummy; } ;
struct fsnotify_group {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __kernel_fsid_t ;
struct TYPE_2__ {int /*<<< orphan*/  mnt_fsnotify_marks; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSNOTIFY_OBJ_TYPE_VFSMOUNT ; 
 int fanotify_add_mark (struct fsnotify_group*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 TYPE_1__* real_mount (struct vfsmount*) ; 

__attribute__((used)) static int fanotify_add_vfsmount_mark(struct fsnotify_group *group,
				      struct vfsmount *mnt, __u32 mask,
				      unsigned int flags, __kernel_fsid_t *fsid)
{
	return fanotify_add_mark(group, &real_mount(mnt)->mnt_fsnotify_marks,
				 FSNOTIFY_OBJ_TYPE_VFSMOUNT, mask, flags, fsid);
}