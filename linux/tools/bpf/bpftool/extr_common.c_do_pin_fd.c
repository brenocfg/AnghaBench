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

/* Variables and functions */
 int bpf_obj_pin (int,char const*) ; 
 int /*<<< orphan*/  errno ; 
 int mount_bpffs_for_pin (char const*) ; 
 int /*<<< orphan*/  p_err (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int do_pin_fd(int fd, const char *name)
{
	int err;

	err = mount_bpffs_for_pin(name);
	if (err)
		return err;

	err = bpf_obj_pin(fd, name);
	if (err)
		p_err("can't pin the object (%s): %s", name, strerror(errno));

	return err;
}