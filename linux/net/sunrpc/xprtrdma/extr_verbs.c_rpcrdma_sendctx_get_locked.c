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
struct TYPE_2__ {int /*<<< orphan*/  empty_sendctx_q; } ;
struct rpcrdma_buffer {unsigned long rb_sc_head; struct rpcrdma_sendctx** rb_sc_ctxs; int /*<<< orphan*/  rb_sc_tail; } ;
struct rpcrdma_xprt {TYPE_1__ rx_stats; int /*<<< orphan*/  rx_xprt; struct rpcrdma_buffer rx_buf; } ;
struct rpcrdma_sendctx {int dummy; } ;

/* Variables and functions */
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long rpcrdma_sendctx_next (struct rpcrdma_buffer*,unsigned long) ; 
 int /*<<< orphan*/  xprt_wait_for_buffer_space (int /*<<< orphan*/ *) ; 

struct rpcrdma_sendctx *rpcrdma_sendctx_get_locked(struct rpcrdma_xprt *r_xprt)
{
	struct rpcrdma_buffer *buf = &r_xprt->rx_buf;
	struct rpcrdma_sendctx *sc;
	unsigned long next_head;

	next_head = rpcrdma_sendctx_next(buf, buf->rb_sc_head);

	if (next_head == READ_ONCE(buf->rb_sc_tail))
		goto out_emptyq;

	/* ORDER: item must be accessed _before_ head is updated */
	sc = buf->rb_sc_ctxs[next_head];

	/* Releasing the lock in the caller acts as a memory
	 * barrier that flushes rb_sc_head.
	 */
	buf->rb_sc_head = next_head;

	return sc;

out_emptyq:
	/* The queue is "empty" if there have not been enough Send
	 * completions recently. This is a sign the Send Queue is
	 * backing up. Cause the caller to pause and try again.
	 */
	xprt_wait_for_buffer_space(&r_xprt->rx_xprt);
	r_xprt->rx_stats.empty_sendctx_q++;
	return NULL;
}