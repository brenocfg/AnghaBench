#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpcrdma_sendctx {unsigned int sc_unmap_count; TYPE_1__* sc_req; struct ib_sge* sc_sges; TYPE_2__* sc_xprt; } ;
struct rpcrdma_ia {int /*<<< orphan*/  ri_device; } ;
struct ib_sge {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {struct rpcrdma_ia rx_ia; } ;
struct TYPE_3__ {int /*<<< orphan*/  rl_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  RPCRDMA_REQ_F_TX_RESOURCES ; 
 int /*<<< orphan*/  ib_dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
rpcrdma_unmap_sendctx(struct rpcrdma_sendctx *sc)
{
	struct rpcrdma_ia *ia = &sc->sc_xprt->rx_ia;
	struct ib_sge *sge;
	unsigned int count;

	/* The first two SGEs contain the transport header and
	 * the inline buffer. These are always left mapped so
	 * they can be cheaply re-used.
	 */
	sge = &sc->sc_sges[2];
	for (count = sc->sc_unmap_count; count; ++sge, --count)
		ib_dma_unmap_page(ia->ri_device,
				  sge->addr, sge->length, DMA_TO_DEVICE);

	if (test_and_clear_bit(RPCRDMA_REQ_F_TX_RESOURCES, &sc->sc_req->rl_flags)) {
		smp_mb__after_atomic();
		wake_up_bit(&sc->sc_req->rl_flags, RPCRDMA_REQ_F_TX_RESOURCES);
	}
}