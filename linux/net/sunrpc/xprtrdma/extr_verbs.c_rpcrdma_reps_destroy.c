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
struct rpcrdma_rep {int dummy; } ;
struct rpcrdma_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpcrdma_rep_destroy (struct rpcrdma_rep*) ; 
 struct rpcrdma_rep* rpcrdma_rep_get_locked (struct rpcrdma_buffer*) ; 

__attribute__((used)) static void rpcrdma_reps_destroy(struct rpcrdma_buffer *buf)
{
	struct rpcrdma_rep *rep;

	while ((rep = rpcrdma_rep_get_locked(buf)) != NULL)
		rpcrdma_rep_destroy(rep);
}