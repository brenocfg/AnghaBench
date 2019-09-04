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
struct path {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 unsigned long AA_MS_IGNORE_MASK ; 
 unsigned long MS_BIND ; 
 unsigned long MS_MGC_MSK ; 
 unsigned long MS_MGC_VAL ; 
 unsigned long MS_MOVE ; 
 unsigned long MS_PRIVATE ; 
 unsigned long MS_REMOUNT ; 
 unsigned long MS_SHARED ; 
 unsigned long MS_SLAVE ; 
 unsigned long MS_UNBINDABLE ; 
 struct aa_label* __begin_current_label_crit_section () ; 
 int /*<<< orphan*/  __end_current_label_crit_section (struct aa_label*) ; 
 int aa_bind_mount (struct aa_label*,struct path const*,char const*,unsigned long) ; 
 int aa_mount_change_type (struct aa_label*,struct path const*,unsigned long) ; 
 int aa_move_mount (struct aa_label*,struct path const*,char const*) ; 
 int aa_new_mount (struct aa_label*,char const*,struct path const*,char const*,unsigned long,void*) ; 
 int aa_remount (struct aa_label*,struct path const*,unsigned long,void*) ; 
 int /*<<< orphan*/  unconfined (struct aa_label*) ; 

__attribute__((used)) static int apparmor_sb_mount(const char *dev_name, const struct path *path,
			     const char *type, unsigned long flags, void *data)
{
	struct aa_label *label;
	int error = 0;

	/* Discard magic */
	if ((flags & MS_MGC_MSK) == MS_MGC_VAL)
		flags &= ~MS_MGC_MSK;

	flags &= ~AA_MS_IGNORE_MASK;

	label = __begin_current_label_crit_section();
	if (!unconfined(label)) {
		if (flags & MS_REMOUNT)
			error = aa_remount(label, path, flags, data);
		else if (flags & MS_BIND)
			error = aa_bind_mount(label, path, dev_name, flags);
		else if (flags & (MS_SHARED | MS_PRIVATE | MS_SLAVE |
				  MS_UNBINDABLE))
			error = aa_mount_change_type(label, path, flags);
		else if (flags & MS_MOVE)
			error = aa_move_mount(label, path, dev_name);
		else
			error = aa_new_mount(label, dev_name, path, type,
					     flags, data);
	}
	__end_current_label_crit_section(label);

	return error;
}