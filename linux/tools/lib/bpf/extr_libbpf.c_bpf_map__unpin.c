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
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int check_path (char const*) ; 
 int errno ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int unlink (char const*) ; 

int bpf_map__unpin(struct bpf_map *map, const char *path)
{
	int err;

	err = check_path(path);
	if (err)
		return err;

	if (map == NULL) {
		pr_warning("invalid map pointer\n");
		return -EINVAL;
	}

	err = unlink(path);
	if (err != 0)
		return -errno;
	pr_debug("unpinned map '%s'\n", path);

	return 0;
}