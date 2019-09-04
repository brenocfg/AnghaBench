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
 scalar_t__ EPERM ; 
 int ERR_MAX_LEN ; 
 int bpf_obj_pin (int,char const*) ; 
 char* dirname (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_bpffs (char*) ; 
 char* malloc (scalar_t__) ; 
 int mnt_bpffs (char*,char*,int) ; 
 int /*<<< orphan*/  p_err (char*,char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char* strerror (scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

int do_pin_fd(int fd, const char *name)
{
	char err_str[ERR_MAX_LEN];
	char *file;
	char *dir;
	int err = 0;

	err = bpf_obj_pin(fd, name);
	if (!err)
		goto out;

	file = malloc(strlen(name) + 1);
	strcpy(file, name);
	dir = dirname(file);

	if (errno != EPERM || is_bpffs(dir)) {
		p_err("can't pin the object (%s): %s", name, strerror(errno));
		goto out_free;
	}

	/* Attempt to mount bpffs, then retry pinning. */
	err = mnt_bpffs(dir, err_str, ERR_MAX_LEN);
	if (!err) {
		err = bpf_obj_pin(fd, name);
		if (err)
			p_err("can't pin the object (%s): %s", name,
			      strerror(errno));
	} else {
		err_str[ERR_MAX_LEN - 1] = '\0';
		p_err("can't mount BPF file system to pin the object (%s): %s",
		      name, err_str);
	}

out_free:
	free(file);
out:
	return err;
}