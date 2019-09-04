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
struct ntb_transport_qp {int link_is_up; int active; scalar_t__ tx_async; scalar_t__ tx_memcpy; scalar_t__ tx_err_no_buf; scalar_t__ tx_ring_full; scalar_t__ tx_pkts; scalar_t__ tx_bytes; scalar_t__ rx_async; scalar_t__ rx_memcpy; scalar_t__ rx_err_ver; scalar_t__ rx_err_oflow; scalar_t__ rx_err_no_buf; scalar_t__ rx_ring_empty; scalar_t__ rx_pkts; scalar_t__ rx_bytes; scalar_t__ rx_index; scalar_t__ tx_index; } ;

/* Variables and functions */

__attribute__((used)) static void ntb_qp_link_down_reset(struct ntb_transport_qp *qp)
{
	qp->link_is_up = false;
	qp->active = false;

	qp->tx_index = 0;
	qp->rx_index = 0;
	qp->rx_bytes = 0;
	qp->rx_pkts = 0;
	qp->rx_ring_empty = 0;
	qp->rx_err_no_buf = 0;
	qp->rx_err_oflow = 0;
	qp->rx_err_ver = 0;
	qp->rx_memcpy = 0;
	qp->rx_async = 0;
	qp->tx_bytes = 0;
	qp->tx_pkts = 0;
	qp->tx_ring_full = 0;
	qp->tx_err_no_buf = 0;
	qp->tx_memcpy = 0;
	qp->tx_async = 0;
}