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
struct rpc_xprt {int bc_alloc_count; int /*<<< orphan*/  bc_free_slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int xprt_dec_alloc_count(struct rpc_xprt *xprt, unsigned int n)
{
	atomic_sub(n, &xprt->bc_free_slots);
	return xprt->bc_alloc_count -= n;
}