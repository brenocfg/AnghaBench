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
struct TYPE_2__ {int /*<<< orphan*/  mnt_fsnotify_marks; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsnotify_destroy_marks (int /*<<< orphan*/ *) ; 
 TYPE_1__* real_mount (struct vfsmount*) ; 

__attribute__((used)) static inline void fsnotify_clear_marks_by_mount(struct vfsmount *mnt)
{
	fsnotify_destroy_marks(&real_mount(mnt)->mnt_fsnotify_marks);
}