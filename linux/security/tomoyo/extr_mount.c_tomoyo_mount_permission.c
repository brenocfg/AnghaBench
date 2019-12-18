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
struct tomoyo_request_info {int dummy; } ;
struct path {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long MS_BIND ; 
 unsigned long MS_MGC_MSK ; 
 unsigned long MS_MGC_VAL ; 
 unsigned long MS_MOVE ; 
 unsigned long MS_PRIVATE ; 
 unsigned long MS_REMOUNT ; 
 unsigned long MS_SHARED ; 
 unsigned long MS_SLAVE ; 
 unsigned long MS_UNBINDABLE ; 
 scalar_t__ TOMOYO_CONFIG_DISABLED ; 
 int /*<<< orphan*/  TOMOYO_MAC_FILE_MOUNT ; 
 size_t TOMOYO_MOUNT_BIND ; 
 size_t TOMOYO_MOUNT_MAKE_PRIVATE ; 
 size_t TOMOYO_MOUNT_MAKE_SHARED ; 
 size_t TOMOYO_MOUNT_MAKE_SLAVE ; 
 size_t TOMOYO_MOUNT_MAKE_UNBINDABLE ; 
 size_t TOMOYO_MOUNT_MOVE ; 
 size_t TOMOYO_MOUNT_REMOUNT ; 
 scalar_t__ tomoyo_init_request_info (struct tomoyo_request_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tomoyo_mount_acl (struct tomoyo_request_info*,char const*,struct path const*,char const*,unsigned long) ; 
 char** tomoyo_mounts ; 
 int tomoyo_read_lock () ; 
 int /*<<< orphan*/  tomoyo_read_unlock (int) ; 

int tomoyo_mount_permission(const char *dev_name, const struct path *path,
			    const char *type, unsigned long flags,
			    void *data_page)
{
	struct tomoyo_request_info r;
	int error;
	int idx;

	if (tomoyo_init_request_info(&r, NULL, TOMOYO_MAC_FILE_MOUNT)
	    == TOMOYO_CONFIG_DISABLED)
		return 0;
	if ((flags & MS_MGC_MSK) == MS_MGC_VAL)
		flags &= ~MS_MGC_MSK;
	if (flags & MS_REMOUNT) {
		type = tomoyo_mounts[TOMOYO_MOUNT_REMOUNT];
		flags &= ~MS_REMOUNT;
	} else if (flags & MS_BIND) {
		type = tomoyo_mounts[TOMOYO_MOUNT_BIND];
		flags &= ~MS_BIND;
	} else if (flags & MS_SHARED) {
		if (flags & (MS_PRIVATE | MS_SLAVE | MS_UNBINDABLE))
			return -EINVAL;
		type = tomoyo_mounts[TOMOYO_MOUNT_MAKE_SHARED];
		flags &= ~MS_SHARED;
	} else if (flags & MS_PRIVATE) {
		if (flags & (MS_SHARED | MS_SLAVE | MS_UNBINDABLE))
			return -EINVAL;
		type = tomoyo_mounts[TOMOYO_MOUNT_MAKE_PRIVATE];
		flags &= ~MS_PRIVATE;
	} else if (flags & MS_SLAVE) {
		if (flags & (MS_SHARED | MS_PRIVATE | MS_UNBINDABLE))
			return -EINVAL;
		type = tomoyo_mounts[TOMOYO_MOUNT_MAKE_SLAVE];
		flags &= ~MS_SLAVE;
	} else if (flags & MS_UNBINDABLE) {
		if (flags & (MS_SHARED | MS_PRIVATE | MS_SLAVE))
			return -EINVAL;
		type = tomoyo_mounts[TOMOYO_MOUNT_MAKE_UNBINDABLE];
		flags &= ~MS_UNBINDABLE;
	} else if (flags & MS_MOVE) {
		type = tomoyo_mounts[TOMOYO_MOUNT_MOVE];
		flags &= ~MS_MOVE;
	}
	if (!type)
		type = "<NULL>";
	idx = tomoyo_read_lock();
	error = tomoyo_mount_acl(&r, dev_name, path, type, flags);
	tomoyo_read_unlock(idx);
	return error;
}