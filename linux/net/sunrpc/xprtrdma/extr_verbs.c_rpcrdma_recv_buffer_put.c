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
struct rpcrdma_rep {TYPE_1__* rr_rxprt; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpcrdma_rep_put (int /*<<< orphan*/ *,struct rpcrdma_rep*) ; 

void rpcrdma_recv_buffer_put(struct rpcrdma_rep *rep)
{
	rpcrdma_rep_put(&rep->rr_rxprt->rx_buf, rep);
}