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
struct gen_pool {int /*<<< orphan*/  data; int /*<<< orphan*/  algo; } ;

/* Variables and functions */
 unsigned long gen_pool_alloc_algo (struct gen_pool*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned long gen_pool_alloc(struct gen_pool *pool, size_t size)
{
	return gen_pool_alloc_algo(pool, size, pool->algo, pool->data);
}