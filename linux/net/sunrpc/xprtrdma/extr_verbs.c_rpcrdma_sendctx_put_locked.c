#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rpcrdma_sendctx {TYPE_1__* sc_xprt; } ;
struct rpcrdma_buffer {unsigned long rb_sc_tail; struct rpcrdma_sendctx** rb_sc_ctxs; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_xprt; struct rpcrdma_buffer rx_buf; } ;

/* Variables and functions */
 unsigned long rpcrdma_sendctx_next (struct rpcrdma_buffer*,unsigned long) ; 
 int /*<<< orphan*/  rpcrdma_sendctx_unmap (struct rpcrdma_sendctx*) ; 
 int /*<<< orphan*/  smp_store_release (unsigned long*,unsigned long) ; 
 int /*<<< orphan*/  xprt_write_space (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rpcrdma_sendctx_put_locked(struct rpcrdma_sendctx *sc)
{
	struct rpcrdma_buffer *buf = &sc->sc_xprt->rx_buf;
	unsigned long next_tail;

	/* Unmap SGEs of previously completed but unsignaled
	 * Sends by walking up the queue until @sc is found.
	 */
	next_tail = buf->rb_sc_tail;
	do {
		next_tail = rpcrdma_sendctx_next(buf, next_tail);

		/* ORDER: item must be accessed _before_ tail is updated */
		rpcrdma_sendctx_unmap(buf->rb_sc_ctxs[next_tail]);

	} while (buf->rb_sc_ctxs[next_tail] != sc);

	/* Paired with READ_ONCE */
	smp_store_release(&buf->rb_sc_tail, next_tail);

	xprt_write_space(&sc->sc_xprt->rx_xprt);
}