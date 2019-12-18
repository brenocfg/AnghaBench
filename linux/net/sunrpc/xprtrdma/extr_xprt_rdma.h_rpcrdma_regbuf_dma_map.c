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
struct rpcrdma_xprt {int dummy; } ;
struct rpcrdma_regbuf {int dummy; } ;

/* Variables and functions */
 int __rpcrdma_regbuf_dma_map (struct rpcrdma_xprt*,struct rpcrdma_regbuf*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcrdma_regbuf_is_mapped (struct rpcrdma_regbuf*) ; 

__attribute__((used)) static inline bool rpcrdma_regbuf_dma_map(struct rpcrdma_xprt *r_xprt,
					  struct rpcrdma_regbuf *rb)
{
	if (likely(rpcrdma_regbuf_is_mapped(rb)))
		return true;
	return __rpcrdma_regbuf_dma_map(r_xprt, rb);
}