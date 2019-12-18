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

/* Variables and functions */
 int /*<<< orphan*/  mempool_free (struct scatterlist*,int /*<<< orphan*/ ) ; 
 int sg_pool_index (unsigned int) ; 
 struct sg_pool* sg_pools ; 

__attribute__((used)) static void sg_pool_free(struct scatterlist *sgl, unsigned int nents)
{
	struct sg_pool *sgp;

	sgp = sg_pools + sg_pool_index(nents);
	mempool_free(sgl, sgp->pool);
}