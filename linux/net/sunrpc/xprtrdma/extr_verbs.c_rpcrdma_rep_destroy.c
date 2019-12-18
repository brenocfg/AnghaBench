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
struct rpcrdma_rep {int /*<<< orphan*/  rr_rdmabuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rpcrdma_rep*) ; 
 int /*<<< orphan*/  rpcrdma_regbuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpcrdma_rep_destroy(struct rpcrdma_rep *rep)
{
	rpcrdma_regbuf_free(rep->rr_rdmabuf);
	kfree(rep);
}