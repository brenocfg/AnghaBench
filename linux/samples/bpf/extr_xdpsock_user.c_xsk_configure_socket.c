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
typedef  int /*<<< orphan*/  u32 ;
struct xsk_umem_info {int /*<<< orphan*/  fq; int /*<<< orphan*/  umem; } ;
struct xsk_socket_info {struct xsk_umem_info* umem; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; int /*<<< orphan*/  xsk; } ;
struct xsk_socket_config {int tx_size; int /*<<< orphan*/  bind_flags; int /*<<< orphan*/  xdp_flags; scalar_t__ libbpf_flags; int /*<<< orphan*/  rx_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSK_RING_CONS__DEFAULT_NUM_DESCS ; 
 int XSK_RING_PROD__DEFAULT_NUM_DESCS ; 
 int bpf_get_link_xdp_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct xsk_socket_info* calloc (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  exit_with_error (int) ; 
 int /*<<< orphan*/  opt_if ; 
 int /*<<< orphan*/  opt_ifindex ; 
 int /*<<< orphan*/  opt_queue ; 
 int /*<<< orphan*/  opt_xdp_bind_flags ; 
 int /*<<< orphan*/  opt_xdp_flags ; 
 int opt_xsk_frame_size ; 
 int /*<<< orphan*/  prog_id ; 
 int* xsk_ring_prod__fill_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xsk_ring_prod__reserve (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsk_ring_prod__submit (int /*<<< orphan*/ *,int) ; 
 int xsk_socket__create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct xsk_socket_config*) ; 

__attribute__((used)) static struct xsk_socket_info *xsk_configure_socket(struct xsk_umem_info *umem)
{
	struct xsk_socket_config cfg;
	struct xsk_socket_info *xsk;
	int ret;
	u32 idx;
	int i;

	xsk = calloc(1, sizeof(*xsk));
	if (!xsk)
		exit_with_error(errno);

	xsk->umem = umem;
	cfg.rx_size = XSK_RING_CONS__DEFAULT_NUM_DESCS;
	cfg.tx_size = XSK_RING_PROD__DEFAULT_NUM_DESCS;
	cfg.libbpf_flags = 0;
	cfg.xdp_flags = opt_xdp_flags;
	cfg.bind_flags = opt_xdp_bind_flags;
	ret = xsk_socket__create(&xsk->xsk, opt_if, opt_queue, umem->umem,
				 &xsk->rx, &xsk->tx, &cfg);
	if (ret)
		exit_with_error(-ret);

	ret = bpf_get_link_xdp_id(opt_ifindex, &prog_id, opt_xdp_flags);
	if (ret)
		exit_with_error(-ret);

	ret = xsk_ring_prod__reserve(&xsk->umem->fq,
				     XSK_RING_PROD__DEFAULT_NUM_DESCS,
				     &idx);
	if (ret != XSK_RING_PROD__DEFAULT_NUM_DESCS)
		exit_with_error(-ret);
	for (i = 0; i < XSK_RING_PROD__DEFAULT_NUM_DESCS; i++)
		*xsk_ring_prod__fill_addr(&xsk->umem->fq, idx++) =
			i * opt_xsk_frame_size;
	xsk_ring_prod__submit(&xsk->umem->fq,
			      XSK_RING_PROD__DEFAULT_NUM_DESCS);

	return xsk;
}