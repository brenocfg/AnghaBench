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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct xdp_sock {int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx; } ;
struct xdp_buff {scalar_t__ handle; } ;

/* Variables and functions */
 int xskq_produce_batch_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __xsk_rcv_zc(struct xdp_sock *xs, struct xdp_buff *xdp, u32 len)
{
	int err = xskq_produce_batch_desc(xs->rx, (u64)xdp->handle, len);

	if (err)
		xs->rx_dropped++;

	return err;
}