#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sxdp ;
struct xsk_umem {scalar_t__ fd; scalar_t__ refcount; } ;
struct xsk_socket_config {int dummy; } ;
struct TYPE_6__ {int rx_size; int tx_size; int libbpf_flags; int /*<<< orphan*/  bind_flags; } ;
struct xsk_socket {scalar_t__ fd; char* ifname; int prog_fd; TYPE_3__ config; int /*<<< orphan*/  queue_id; scalar_t__ ifindex; struct xsk_ring_prod* tx; struct xsk_ring_cons* rx; struct xsk_umem* umem; scalar_t__ outstanding_tx; } ;
struct xsk_ring_prod {int mask; int size; int cached_cons; void* ring; void* flags; void* consumer; void* producer; } ;
struct xsk_ring_cons {int mask; int size; void* ring; void* flags; void* consumer; void* producer; } ;
struct TYPE_4__ {int desc; int producer; int consumer; int flags; } ;
struct TYPE_5__ {int desc; int producer; int consumer; int flags; } ;
struct xdp_mmap_offsets {TYPE_1__ rx; TYPE_2__ tx; } ;
struct xdp_desc {int dummy; } ;
struct sockaddr_xdp {int /*<<< orphan*/  sxdp_flags; int /*<<< orphan*/  sxdp_queue_id; scalar_t__ sxdp_ifindex; int /*<<< orphan*/  sxdp_family; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  off ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_XDP ; 
 int EBUSY ; 
 int EFAULT ; 
 int ENOMEM ; 
 int IFNAMSIZ ; 
 void* MAP_FAILED ; 
 int MAP_POPULATE ; 
 int MAP_SHARED ; 
 int /*<<< orphan*/  PF_XDP ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  SOL_XDP ; 
 int /*<<< orphan*/  XDP_MMAP_OFFSETS ; 
 int /*<<< orphan*/  XDP_PGOFF_RX_RING ; 
 int /*<<< orphan*/  XDP_PGOFF_TX_RING ; 
 int /*<<< orphan*/  XDP_RX_RING ; 
 int /*<<< orphan*/  XDP_TX_RING ; 
 int XSK_LIBBPF_FLAGS__INHIBIT_PROG_LOAD ; 
 int bind (scalar_t__,struct sockaddr*,int) ; 
 struct xsk_socket* calloc (int,int) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct xsk_socket*) ; 
 int getsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xdp_mmap_offsets*,int*) ; 
 scalar_t__ if_nametoindex (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 void* mmap (int /*<<< orphan*/ *,int,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,int) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xsk_set_xdp_socket_config (TYPE_3__*,struct xsk_socket_config const*) ; 
 int xsk_setup_xdp_prog (struct xsk_socket*) ; 

int xsk_socket__create(struct xsk_socket **xsk_ptr, const char *ifname,
		       __u32 queue_id, struct xsk_umem *umem,
		       struct xsk_ring_cons *rx, struct xsk_ring_prod *tx,
		       const struct xsk_socket_config *usr_config)
{
	void *rx_map = NULL, *tx_map = NULL;
	struct sockaddr_xdp sxdp = {};
	struct xdp_mmap_offsets off;
	struct xsk_socket *xsk;
	socklen_t optlen;
	int err;

	if (!umem || !xsk_ptr || !rx || !tx)
		return -EFAULT;

	if (umem->refcount) {
		pr_warning("Error: shared umems not supported by libbpf.\n");
		return -EBUSY;
	}

	xsk = calloc(1, sizeof(*xsk));
	if (!xsk)
		return -ENOMEM;

	if (umem->refcount++ > 0) {
		xsk->fd = socket(AF_XDP, SOCK_RAW, 0);
		if (xsk->fd < 0) {
			err = -errno;
			goto out_xsk_alloc;
		}
	} else {
		xsk->fd = umem->fd;
	}

	xsk->outstanding_tx = 0;
	xsk->queue_id = queue_id;
	xsk->umem = umem;
	xsk->ifindex = if_nametoindex(ifname);
	if (!xsk->ifindex) {
		err = -errno;
		goto out_socket;
	}
	memcpy(xsk->ifname, ifname, IFNAMSIZ - 1);
	xsk->ifname[IFNAMSIZ - 1] = '\0';

	err = xsk_set_xdp_socket_config(&xsk->config, usr_config);
	if (err)
		goto out_socket;

	if (rx) {
		err = setsockopt(xsk->fd, SOL_XDP, XDP_RX_RING,
				 &xsk->config.rx_size,
				 sizeof(xsk->config.rx_size));
		if (err) {
			err = -errno;
			goto out_socket;
		}
	}
	if (tx) {
		err = setsockopt(xsk->fd, SOL_XDP, XDP_TX_RING,
				 &xsk->config.tx_size,
				 sizeof(xsk->config.tx_size));
		if (err) {
			err = -errno;
			goto out_socket;
		}
	}

	optlen = sizeof(off);
	err = getsockopt(xsk->fd, SOL_XDP, XDP_MMAP_OFFSETS, &off, &optlen);
	if (err) {
		err = -errno;
		goto out_socket;
	}

	if (rx) {
		rx_map = mmap(NULL, off.rx.desc +
			      xsk->config.rx_size * sizeof(struct xdp_desc),
			      PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE,
			      xsk->fd, XDP_PGOFF_RX_RING);
		if (rx_map == MAP_FAILED) {
			err = -errno;
			goto out_socket;
		}

		rx->mask = xsk->config.rx_size - 1;
		rx->size = xsk->config.rx_size;
		rx->producer = rx_map + off.rx.producer;
		rx->consumer = rx_map + off.rx.consumer;
		rx->flags = rx_map + off.rx.flags;
		rx->ring = rx_map + off.rx.desc;
	}
	xsk->rx = rx;

	if (tx) {
		tx_map = mmap(NULL, off.tx.desc +
			      xsk->config.tx_size * sizeof(struct xdp_desc),
			      PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE,
			      xsk->fd, XDP_PGOFF_TX_RING);
		if (tx_map == MAP_FAILED) {
			err = -errno;
			goto out_mmap_rx;
		}

		tx->mask = xsk->config.tx_size - 1;
		tx->size = xsk->config.tx_size;
		tx->producer = tx_map + off.tx.producer;
		tx->consumer = tx_map + off.tx.consumer;
		tx->flags = tx_map + off.tx.flags;
		tx->ring = tx_map + off.tx.desc;
		tx->cached_cons = xsk->config.tx_size;
	}
	xsk->tx = tx;

	sxdp.sxdp_family = PF_XDP;
	sxdp.sxdp_ifindex = xsk->ifindex;
	sxdp.sxdp_queue_id = xsk->queue_id;
	sxdp.sxdp_flags = xsk->config.bind_flags;

	err = bind(xsk->fd, (struct sockaddr *)&sxdp, sizeof(sxdp));
	if (err) {
		err = -errno;
		goto out_mmap_tx;
	}

	xsk->prog_fd = -1;

	if (!(xsk->config.libbpf_flags & XSK_LIBBPF_FLAGS__INHIBIT_PROG_LOAD)) {
		err = xsk_setup_xdp_prog(xsk);
		if (err)
			goto out_mmap_tx;
	}

	*xsk_ptr = xsk;
	return 0;

out_mmap_tx:
	if (tx)
		munmap(tx_map, off.tx.desc +
		       xsk->config.tx_size * sizeof(struct xdp_desc));
out_mmap_rx:
	if (rx)
		munmap(rx_map, off.rx.desc +
		       xsk->config.rx_size * sizeof(struct xdp_desc));
out_socket:
	if (--umem->refcount)
		close(xsk->fd);
out_xsk_alloc:
	free(xsk);
	return err;
}