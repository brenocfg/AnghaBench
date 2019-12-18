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
struct rpcrdma_rep {int /*<<< orphan*/  rr_node; int /*<<< orphan*/  rr_temp; } ;
struct rpcrdma_buffer {int /*<<< orphan*/  rb_free_reps; } ;

/* Variables and functions */
 int /*<<< orphan*/  llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpcrdma_rep_destroy (struct rpcrdma_rep*) ; 

__attribute__((used)) static void rpcrdma_rep_put(struct rpcrdma_buffer *buf,
			    struct rpcrdma_rep *rep)
{
	if (!rep->rr_temp)
		llist_add(&rep->rr_node, &buf->rb_free_reps);
	else
		rpcrdma_rep_destroy(rep);
}