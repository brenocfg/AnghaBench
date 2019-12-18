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
 scalar_t__ block_mount ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_bpffs (char*) ; 
 char* malloc (scalar_t__) ; 
 int mnt_fs (char*,char*,char*,int) ; 
 int /*<<< orphan*/  p_err (char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

int mount_bpffs_for_pin(const char *name)
{
	char err_str[ERR_MAX_LEN];
	char *file;
	char *dir;
	int err = 0;

	file = malloc(strlen(name) + 1);
	strcpy(file, name);
	dir = dirname(file);

	if (is_bpffs(dir))
		/* nothing to do if already mounted */
		goto out_free;

	if (block_mount) {
		p_err("no BPF file system found, not mounting it due to --nomount option");
		err = -1;
		goto out_free;
	}

	err = mnt_fs(dir, "bpf", err_str, ERR_MAX_LEN);
	if (err) {
		err_str[ERR_MAX_LEN - 1] = '\0';
		p_err("can't mount BPF file system to pin the object (%s): %s",
		      name, err_str);
	}

out_free:
	free(file);
	return err;
}