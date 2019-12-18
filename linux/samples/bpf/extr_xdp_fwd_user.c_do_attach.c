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
 int bpf_map_update_elem (int,int*,int*,int /*<<< orphan*/ ) ; 
 int bpf_set_link_xdp_fd (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static int do_attach(int idx, int prog_fd, int map_fd, const char *name)
{
	int err;

	err = bpf_set_link_xdp_fd(idx, prog_fd, 0);
	if (err < 0) {
		printf("ERROR: failed to attach program to %s\n", name);
		return err;
	}

	/* Adding ifindex as a possible egress TX port */
	err = bpf_map_update_elem(map_fd, &idx, &idx, 0);
	if (err)
		printf("ERROR: failed using device %s as TX-port\n", name);

	return err;
}