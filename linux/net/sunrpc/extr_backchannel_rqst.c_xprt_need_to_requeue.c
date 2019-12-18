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
struct rpc_xprt {scalar_t__ bc_alloc_count; scalar_t__ bc_alloc_max; } ;

/* Variables and functions */

__attribute__((used)) static inline int xprt_need_to_requeue(struct rpc_xprt *xprt)
{
	return xprt->bc_alloc_count < xprt->bc_alloc_max;
}