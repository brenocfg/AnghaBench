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
struct TYPE_2__ {int nr; int* fds; } ;
struct bpf_program {int /*<<< orphan*/  section_name; TYPE_1__ instances; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  pr_warning (char*,int,int /*<<< orphan*/ ,...) ; 

int bpf_program__nth_fd(const struct bpf_program *prog, int n)
{
	int fd;

	if (!prog)
		return -EINVAL;

	if (n >= prog->instances.nr || n < 0) {
		pr_warning("Can't get the %dth fd from program %s: only %d instances\n",
			   n, prog->section_name, prog->instances.nr);
		return -EINVAL;
	}

	fd = prog->instances.fds[n];
	if (fd < 0) {
		pr_warning("%dth instance of program '%s' is invalid\n",
			   n, prog->section_name);
		return -ENOENT;
	}

	return fd;
}