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
struct file_handle {int handle_bytes; int /*<<< orphan*/  f_handle; } ;

/* Variables and functions */
 int AT_FDCWD ; 
 int /*<<< orphan*/  PATH_MAX ; 
 struct file_handle* calloc (int,int) ; 
 int /*<<< orphan*/  format_cgroup_path (char*,char const*) ; 
 int /*<<< orphan*/  free (struct file_handle*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int name_to_handle_at (int,char*,struct file_handle*,int*,int) ; 
 struct file_handle* realloc (struct file_handle*,int) ; 

unsigned long long get_cgroup_id(const char *path)
{
	int dirfd, err, flags, mount_id, fhsize;
	union {
		unsigned long long cgid;
		unsigned char raw_bytes[8];
	} id;
	char cgroup_workdir[PATH_MAX + 1];
	struct file_handle *fhp, *fhp2;
	unsigned long long ret = 0;

	format_cgroup_path(cgroup_workdir, path);

	dirfd = AT_FDCWD;
	flags = 0;
	fhsize = sizeof(*fhp);
	fhp = calloc(1, fhsize);
	if (!fhp) {
		log_err("calloc");
		return 0;
	}
	err = name_to_handle_at(dirfd, cgroup_workdir, fhp, &mount_id, flags);
	if (err >= 0 || fhp->handle_bytes != 8) {
		log_err("name_to_handle_at");
		goto free_mem;
	}

	fhsize = sizeof(struct file_handle) + fhp->handle_bytes;
	fhp2 = realloc(fhp, fhsize);
	if (!fhp2) {
		log_err("realloc");
		goto free_mem;
	}
	err = name_to_handle_at(dirfd, cgroup_workdir, fhp2, &mount_id, flags);
	fhp = fhp2;
	if (err < 0) {
		log_err("name_to_handle_at");
		goto free_mem;
	}

	memcpy(id.raw_bytes, fhp->f_handle, 8);
	ret = id.cgid;

free_mem:
	free(fhp);
	return ret;
}