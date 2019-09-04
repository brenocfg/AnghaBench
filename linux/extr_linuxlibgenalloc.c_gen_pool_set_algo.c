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
struct gen_pool {void* data; scalar_t__ algo; } ;
typedef  scalar_t__ genpool_algo_t ;

/* Variables and functions */
 scalar_t__ gen_pool_first_fit ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void gen_pool_set_algo(struct gen_pool *pool, genpool_algo_t algo, void *data)
{
	rcu_read_lock();

	pool->algo = algo;
	if (!pool->algo)
		pool->algo = gen_pool_first_fit;

	pool->data = data;

	rcu_read_unlock();
}