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
struct bpf_prog_info {int dummy; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int __u32 ;

/* Variables and functions */
 int bpf_obj_get_info_by_fd (int,struct bpf_prog_info*,int*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  p_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_prog_json (struct bpf_prog_info*,int) ; 
 int /*<<< orphan*/  print_prog_plain (struct bpf_prog_info*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int show_prog(int fd)
{
	struct bpf_prog_info info = {};
	__u32 len = sizeof(info);
	int err;

	err = bpf_obj_get_info_by_fd(fd, &info, &len);
	if (err) {
		p_err("can't get prog info: %s", strerror(errno));
		return -1;
	}

	if (json_output)
		print_prog_json(&info, fd);
	else
		print_prog_plain(&info, fd);

	return 0;
}