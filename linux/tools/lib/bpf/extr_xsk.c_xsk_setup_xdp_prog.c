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
struct TYPE_2__ {int /*<<< orphan*/  xdp_flags; } ;
struct xsk_socket {int /*<<< orphan*/  prog_fd; TYPE_1__ config; int /*<<< orphan*/  ifindex; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int bpf_get_link_xdp_id (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_get_fd_by_id (scalar_t__) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int xsk_create_bpf_maps (struct xsk_socket*) ; 
 int /*<<< orphan*/  xsk_delete_bpf_maps (struct xsk_socket*) ; 
 int xsk_load_xdp_prog (struct xsk_socket*) ; 
 int xsk_lookup_bpf_maps (struct xsk_socket*) ; 
 int xsk_set_bpf_maps (struct xsk_socket*) ; 

__attribute__((used)) static int xsk_setup_xdp_prog(struct xsk_socket *xsk)
{
	__u32 prog_id = 0;
	int err;

	err = bpf_get_link_xdp_id(xsk->ifindex, &prog_id,
				  xsk->config.xdp_flags);
	if (err)
		return err;

	if (!prog_id) {
		err = xsk_create_bpf_maps(xsk);
		if (err)
			return err;

		err = xsk_load_xdp_prog(xsk);
		if (err) {
			xsk_delete_bpf_maps(xsk);
			return err;
		}
	} else {
		xsk->prog_fd = bpf_prog_get_fd_by_id(prog_id);
		err = xsk_lookup_bpf_maps(xsk);
		if (err) {
			close(xsk->prog_fd);
			return err;
		}
	}

	err = xsk_set_bpf_maps(xsk);
	if (err) {
		xsk_delete_bpf_maps(xsk);
		close(xsk->prog_fd);
		return err;
	}

	return 0;
}