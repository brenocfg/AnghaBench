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
struct sg_pool {int /*<<< orphan*/  pool; } ;
struct scatterlist {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct scatterlist* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sg_pool_index (unsigned int) ; 
 struct sg_pool* sg_pools ; 

__attribute__((used)) static struct scatterlist *sg_pool_alloc(unsigned int nents, gfp_t gfp_mask)
{
	struct sg_pool *sgp;

	sgp = sg_pools + sg_pool_index(nents);
	return mempool_alloc(sgp->pool, gfp_mask);
}