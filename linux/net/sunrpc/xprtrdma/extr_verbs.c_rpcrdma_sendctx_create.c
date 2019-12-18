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
struct TYPE_3__ {int /*<<< orphan*/  done; } ;
struct TYPE_4__ {int /*<<< orphan*/  opcode; int /*<<< orphan*/  sg_list; TYPE_1__* wr_cqe; } ;
struct rpcrdma_sendctx {TYPE_1__ sc_cqe; TYPE_2__ sc_wr; int /*<<< orphan*/  sc_sges; } ;
struct rpcrdma_ia {int /*<<< orphan*/  ri_max_send_sges; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 struct rpcrdma_sendctx* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcrdma_wc_send ; 
 int /*<<< orphan*/  sc_sges ; 
 int /*<<< orphan*/  struct_size (struct rpcrdma_sendctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rpcrdma_sendctx *rpcrdma_sendctx_create(struct rpcrdma_ia *ia)
{
	struct rpcrdma_sendctx *sc;

	sc = kzalloc(struct_size(sc, sc_sges, ia->ri_max_send_sges),
		     GFP_KERNEL);
	if (!sc)
		return NULL;

	sc->sc_wr.wr_cqe = &sc->sc_cqe;
	sc->sc_wr.sg_list = sc->sc_sges;
	sc->sc_wr.opcode = IB_WR_SEND;
	sc->sc_cqe.done = rpcrdma_wc_send;
	return sc;
}