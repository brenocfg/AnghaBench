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
struct rpc_xprt_iter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xprt_iter_xchg_switch (struct rpc_xprt_iter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_switch_put (int /*<<< orphan*/ ) ; 

void xprt_iter_destroy(struct rpc_xprt_iter *xpi)
{
	xprt_switch_put(xprt_iter_xchg_switch(xpi, NULL));
}