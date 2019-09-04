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
struct rpcrdma_mr {int dummy; } ;
struct rpcrdma_buffer {int /*<<< orphan*/  rb_mrlock; int /*<<< orphan*/  rb_mrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpcrdma_mr_push (struct rpcrdma_mr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__rpcrdma_mr_put(struct rpcrdma_buffer *buf, struct rpcrdma_mr *mr)
{
	spin_lock(&buf->rb_mrlock);
	rpcrdma_mr_push(mr, &buf->rb_mrs);
	spin_unlock(&buf->rb_mrlock);
}