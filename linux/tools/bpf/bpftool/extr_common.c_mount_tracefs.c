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
 int ERR_MAX_LEN ; 
 int mnt_fs (char const*,char*,char*,int) ; 
 int /*<<< orphan*/  p_err (char*,char*) ; 

int mount_tracefs(const char *target)
{
	char err_str[ERR_MAX_LEN];
	int err;

	err = mnt_fs(target, "tracefs", err_str, ERR_MAX_LEN);
	if (err) {
		err_str[ERR_MAX_LEN - 1] = '\0';
		p_err("can't mount tracefs: %s", err_str);
	}

	return err;
}