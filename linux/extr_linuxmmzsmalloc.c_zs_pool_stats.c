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
struct zs_pool_stats {int dummy; } ;
struct zs_pool {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct zs_pool_stats*,int /*<<< orphan*/ *,int) ; 

void zs_pool_stats(struct zs_pool *pool, struct zs_pool_stats *stats)
{
	memcpy(stats, &pool->stats, sizeof(struct zs_pool_stats));
}