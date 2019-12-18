#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nr; } ;
struct bpf_program {TYPE_1__ instances; int /*<<< orphan*/  section_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int check_path (char const*) ; 
 int errno ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 int unlink (char const*) ; 

int bpf_program__unpin_instance(struct bpf_program *prog, const char *path,
				int instance)
{
	int err;

	err = check_path(path);
	if (err)
		return err;

	if (prog == NULL) {
		pr_warning("invalid program pointer\n");
		return -EINVAL;
	}

	if (instance < 0 || instance >= prog->instances.nr) {
		pr_warning("invalid prog instance %d of prog %s (max %d)\n",
			   instance, prog->section_name, prog->instances.nr);
		return -EINVAL;
	}

	err = unlink(path);
	if (err != 0)
		return -errno;
	pr_debug("unpinned program '%s'\n", path);

	return 0;
}