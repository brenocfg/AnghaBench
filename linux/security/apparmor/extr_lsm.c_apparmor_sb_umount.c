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
struct vfsmount {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 struct aa_label* __begin_current_label_crit_section () ; 
 int /*<<< orphan*/  __end_current_label_crit_section (struct aa_label*) ; 
 int aa_umount (struct aa_label*,struct vfsmount*,int) ; 
 int /*<<< orphan*/  unconfined (struct aa_label*) ; 

__attribute__((used)) static int apparmor_sb_umount(struct vfsmount *mnt, int flags)
{
	struct aa_label *label;
	int error = 0;

	label = __begin_current_label_crit_section();
	if (!unconfined(label))
		error = aa_umount(label, mnt, flags);
	__end_current_label_crit_section(label);

	return error;
}