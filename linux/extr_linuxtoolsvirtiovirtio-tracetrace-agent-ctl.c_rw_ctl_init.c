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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int rw_ctl_init(const char *ctl_path)
{
	int ctl_fd;

	ctl_fd = open(ctl_path, O_RDONLY);
	if (ctl_fd == -1) {
		pr_err("Cannot open ctl_fd\n");
		goto error;
	}

	return ctl_fd;

error:
	exit(EXIT_FAILURE);
}