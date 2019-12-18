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
struct rds_tcp_connection {int /*<<< orphan*/  t_tcp_node; int /*<<< orphan*/  t_tcp_node_detached; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct rds_tcp_connection*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_tcp_conn_lock ; 
 int /*<<< orphan*/  rds_tcp_conn_slab ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_tcp_connection*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rds_tcp_conn_free(void *arg)
{
	struct rds_tcp_connection *tc = arg;
	unsigned long flags;

	rdsdebug("freeing tc %p\n", tc);

	spin_lock_irqsave(&rds_tcp_conn_lock, flags);
	if (!tc->t_tcp_node_detached)
		list_del(&tc->t_tcp_node);
	spin_unlock_irqrestore(&rds_tcp_conn_lock, flags);

	kmem_cache_free(rds_tcp_conn_slab, tc);
}