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
typedef  enum bpf_obj_type { ____Placeholder_bpf_obj_type } bpf_obj_type ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int get_fd_type (int) ; 
 int /*<<< orphan*/  get_fd_type_name (int) ; 
 int open_obj_pinned (char*,int) ; 
 int /*<<< orphan*/  p_err (char*,int /*<<< orphan*/ ) ; 

int open_obj_pinned_any(char *path, enum bpf_obj_type exp_type)
{
	enum bpf_obj_type type;
	int fd;

	fd = open_obj_pinned(path, false);
	if (fd < 0)
		return -1;

	type = get_fd_type(fd);
	if (type < 0) {
		close(fd);
		return type;
	}
	if (type != exp_type) {
		p_err("incorrect object type: %s", get_fd_type_name(type));
		close(fd);
		return -1;
	}

	return fd;
}