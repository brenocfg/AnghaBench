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
struct statfs {scalar_t__ f_type; } ;
typedef  int /*<<< orphan*/  errmsg ;

/* Variables and functions */
 scalar_t__ BPF_FS_MAGIC ; 
 int EINVAL ; 
 int ENOMEM ; 
 int STRERR_BUFSIZE ; 
 char* dirname (char*) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* libbpf_strerror_r (int,char*,int) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*,...) ; 
 scalar_t__ statfs (char*,struct statfs*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int check_path(const char *path)
{
	char *cp, errmsg[STRERR_BUFSIZE];
	struct statfs st_fs;
	char *dname, *dir;
	int err = 0;

	if (path == NULL)
		return -EINVAL;

	dname = strdup(path);
	if (dname == NULL)
		return -ENOMEM;

	dir = dirname(dname);
	if (statfs(dir, &st_fs)) {
		cp = libbpf_strerror_r(errno, errmsg, sizeof(errmsg));
		pr_warning("failed to statfs %s: %s\n", dir, cp);
		err = -errno;
	}
	free(dname);

	if (!err && st_fs.f_type != BPF_FS_MAGIC) {
		pr_warning("specified path %s is not on BPF FS\n", path);
		err = -EINVAL;
	}

	return err;
}