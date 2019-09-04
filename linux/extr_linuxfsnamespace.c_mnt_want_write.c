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
struct vfsmount {int /*<<< orphan*/  mnt_sb; } ;

/* Variables and functions */
 int __mnt_want_write (struct vfsmount*) ; 
 int /*<<< orphan*/  sb_end_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_write (int /*<<< orphan*/ ) ; 

int mnt_want_write(struct vfsmount *m)
{
	int ret;

	sb_start_write(m->mnt_sb);
	ret = __mnt_want_write(m);
	if (ret)
		sb_end_write(m->mnt_sb);
	return ret;
}