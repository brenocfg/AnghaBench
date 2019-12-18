#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t rx_size; size_t tx_size; } ;
struct xsk_socket {int prog_fd; scalar_t__ fd; TYPE_6__* umem; TYPE_5__ config; TYPE_3__* tx; TYPE_1__* rx; } ;
struct TYPE_10__ {scalar_t__ desc; } ;
struct TYPE_8__ {scalar_t__ desc; } ;
struct xdp_mmap_offsets {TYPE_4__ tx; TYPE_2__ rx; } ;
struct xdp_desc {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  off ;
struct TYPE_12__ {scalar_t__ fd; int /*<<< orphan*/  refcount; } ;
struct TYPE_9__ {scalar_t__ ring; } ;
struct TYPE_7__ {scalar_t__ ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_XDP ; 
 int /*<<< orphan*/  XDP_MMAP_OFFSETS ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (struct xsk_socket*) ; 
 int getsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xdp_mmap_offsets*,int*) ; 
 int /*<<< orphan*/  munmap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xsk_delete_bpf_maps (struct xsk_socket*) ; 

void xsk_socket__delete(struct xsk_socket *xsk)
{
	size_t desc_sz = sizeof(struct xdp_desc);
	struct xdp_mmap_offsets off;
	socklen_t optlen;
	int err;

	if (!xsk)
		return;

	if (xsk->prog_fd != -1) {
		xsk_delete_bpf_maps(xsk);
		close(xsk->prog_fd);
	}

	optlen = sizeof(off);
	err = getsockopt(xsk->fd, SOL_XDP, XDP_MMAP_OFFSETS, &off, &optlen);
	if (!err) {
		if (xsk->rx) {
			munmap(xsk->rx->ring - off.rx.desc,
			       off.rx.desc + xsk->config.rx_size * desc_sz);
		}
		if (xsk->tx) {
			munmap(xsk->tx->ring - off.tx.desc,
			       off.tx.desc + xsk->config.tx_size * desc_sz);
		}

	}

	xsk->umem->refcount--;
	/* Do not close an fd that also has an associated umem connected
	 * to it.
	 */
	if (xsk->fd != xsk->umem->fd)
		close(xsk->fd);
	free(xsk);
}