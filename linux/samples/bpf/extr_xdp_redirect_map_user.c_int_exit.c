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
 scalar_t__ bpf_get_link_xdp_id (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_set_link_xdp_fd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dummy_prog_id ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  ifindex_in ; 
 int /*<<< orphan*/  ifindex_out ; 
 scalar_t__ ifindex_out_xdp_dummy_attached ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ prog_id ; 
 int /*<<< orphan*/  xdp_flags ; 

__attribute__((used)) static void int_exit(int sig)
{
	__u32 curr_prog_id = 0;

	if (bpf_get_link_xdp_id(ifindex_in, &curr_prog_id, xdp_flags)) {
		printf("bpf_get_link_xdp_id failed\n");
		exit(1);
	}
	if (prog_id == curr_prog_id)
		bpf_set_link_xdp_fd(ifindex_in, -1, xdp_flags);
	else if (!curr_prog_id)
		printf("couldn't find a prog id on iface IN\n");
	else
		printf("program on iface IN changed, not removing\n");

	if (ifindex_out_xdp_dummy_attached) {
		curr_prog_id = 0;
		if (bpf_get_link_xdp_id(ifindex_out, &curr_prog_id,
					xdp_flags)) {
			printf("bpf_get_link_xdp_id failed\n");
			exit(1);
		}
		if (dummy_prog_id == curr_prog_id)
			bpf_set_link_xdp_fd(ifindex_out, -1, xdp_flags);
		else if (!curr_prog_id)
			printf("couldn't find a prog id on iface OUT\n");
		else
			printf("program on iface OUT changed, not removing\n");
	}
	exit(0);
}