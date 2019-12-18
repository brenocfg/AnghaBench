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
struct xsk_socket {int /*<<< orphan*/  xsks_map_fd; int /*<<< orphan*/  queue_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_map_delete_elem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xsk_delete_bpf_maps(struct xsk_socket *xsk)
{
	bpf_map_delete_elem(xsk->xsks_map_fd, &xsk->queue_id);
	close(xsk->xsks_map_fd);
}