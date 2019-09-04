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
struct rpcrdma_mr {TYPE_1__* mr_xprt; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rpcrdma_mr_put (int /*<<< orphan*/ *,struct rpcrdma_mr*) ; 

void
rpcrdma_mr_put(struct rpcrdma_mr *mr)
{
	__rpcrdma_mr_put(&mr->mr_xprt->rx_buf, mr);
}