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
struct TYPE_2__ {size_t hardway_register_count; } ;
struct rpcrdma_xprt {TYPE_1__ rx_stats; } ;
struct rpcrdma_regbuf {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 size_t rdmab_length (struct rpcrdma_regbuf*) ; 
 int /*<<< orphan*/  rpcrdma_regbuf_realloc (struct rpcrdma_regbuf*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool rpcrdma_check_regbuf(struct rpcrdma_xprt *r_xprt,
				 struct rpcrdma_regbuf *rb, size_t size,
				 gfp_t flags)
{
	if (unlikely(rdmab_length(rb) < size)) {
		if (!rpcrdma_regbuf_realloc(rb, size, flags))
			return false;
		r_xprt->rx_stats.hardway_register_count += size;
	}
	return true;
}