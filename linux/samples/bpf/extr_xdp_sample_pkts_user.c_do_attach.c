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
struct bpf_prog_info {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int __u32 ;

/* Variables and functions */
 int bpf_obj_get_info_by_fd (int,struct bpf_prog_info*,int*) ; 
 int bpf_set_link_xdp_fd (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  prog_id ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdp_flags ; 

__attribute__((used)) static int do_attach(int idx, int fd, const char *name)
{
	struct bpf_prog_info info = {};
	__u32 info_len = sizeof(info);
	int err;

	err = bpf_set_link_xdp_fd(idx, fd, xdp_flags);
	if (err < 0) {
		printf("ERROR: failed to attach program to %s\n", name);
		return err;
	}

	err = bpf_obj_get_info_by_fd(fd, &info, &info_len);
	if (err) {
		printf("can't get prog info - %s\n", strerror(errno));
		return err;
	}
	prog_id = info.id;

	return err;
}