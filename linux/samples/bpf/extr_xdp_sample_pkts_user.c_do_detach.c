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
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int bpf_get_link_xdp_id (int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int bpf_set_link_xdp_fd (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ prog_id ; 

__attribute__((used)) static int do_detach(int idx, const char *name)
{
	__u32 curr_prog_id = 0;
	int err = 0;

	err = bpf_get_link_xdp_id(idx, &curr_prog_id, 0);
	if (err) {
		printf("bpf_get_link_xdp_id failed\n");
		return err;
	}
	if (prog_id == curr_prog_id) {
		err = bpf_set_link_xdp_fd(idx, -1, 0);
		if (err < 0)
			printf("ERROR: failed to detach prog from %s\n", name);
	} else if (!curr_prog_id) {
		printf("couldn't find a prog id on a %s\n", name);
	} else {
		printf("program on interface changed, not removing\n");
	}

	return err;
}