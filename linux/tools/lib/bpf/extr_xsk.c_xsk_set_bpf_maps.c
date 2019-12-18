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
struct xsk_socket {int /*<<< orphan*/  fd; int /*<<< orphan*/  queue_id; int /*<<< orphan*/  xsks_map_fd; } ;

/* Variables and functions */
 int bpf_map_update_elem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xsk_set_bpf_maps(struct xsk_socket *xsk)
{
	return bpf_map_update_elem(xsk->xsks_map_fd, &xsk->queue_id,
				   &xsk->fd, 0);
}