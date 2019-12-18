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
struct bpf_map {int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  errmsg ;

/* Variables and functions */
 int EINVAL ; 
 int STRERR_BUFSIZE ; 
 scalar_t__ bpf_obj_pin (int /*<<< orphan*/ ,char const*) ; 
 int check_path (char const*) ; 
 int errno ; 
 char* libbpf_strerror_r (int,char*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 

int bpf_map__pin(struct bpf_map *map, const char *path)
{
	char *cp, errmsg[STRERR_BUFSIZE];
	int err;

	err = check_path(path);
	if (err)
		return err;

	if (map == NULL) {
		pr_warning("invalid map pointer\n");
		return -EINVAL;
	}

	if (bpf_obj_pin(map->fd, path)) {
		cp = libbpf_strerror_r(errno, errmsg, sizeof(errmsg));
		pr_warning("failed to pin map: %s\n", cp);
		return -errno;
	}

	pr_debug("pinned map '%s'\n", path);

	return 0;
}