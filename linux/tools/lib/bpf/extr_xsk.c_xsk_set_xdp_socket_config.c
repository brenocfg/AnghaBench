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
struct xsk_socket_config {int libbpf_flags; scalar_t__ bind_flags; scalar_t__ xdp_flags; int /*<<< orphan*/  tx_size; int /*<<< orphan*/  rx_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int XSK_LIBBPF_FLAGS__INHIBIT_PROG_LOAD ; 
 int /*<<< orphan*/  XSK_RING_CONS__DEFAULT_NUM_DESCS ; 
 int /*<<< orphan*/  XSK_RING_PROD__DEFAULT_NUM_DESCS ; 

__attribute__((used)) static int xsk_set_xdp_socket_config(struct xsk_socket_config *cfg,
				     const struct xsk_socket_config *usr_cfg)
{
	if (!usr_cfg) {
		cfg->rx_size = XSK_RING_CONS__DEFAULT_NUM_DESCS;
		cfg->tx_size = XSK_RING_PROD__DEFAULT_NUM_DESCS;
		cfg->libbpf_flags = 0;
		cfg->xdp_flags = 0;
		cfg->bind_flags = 0;
		return 0;
	}

	if (usr_cfg->libbpf_flags & ~XSK_LIBBPF_FLAGS__INHIBIT_PROG_LOAD)
		return -EINVAL;

	cfg->rx_size = usr_cfg->rx_size;
	cfg->tx_size = usr_cfg->tx_size;
	cfg->libbpf_flags = usr_cfg->libbpf_flags;
	cfg->xdp_flags = usr_cfg->xdp_flags;
	cfg->bind_flags = usr_cfg->bind_flags;

	return 0;
}