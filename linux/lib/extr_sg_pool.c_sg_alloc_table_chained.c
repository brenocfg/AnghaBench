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
struct sg_table {int nents; int orig_nents; int /*<<< orphan*/  sgl; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SG_CHUNK_SIZE ; 
 int __sg_alloc_table (struct sg_table*,int,int /*<<< orphan*/ ,struct scatterlist*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_free_table_chained (struct sg_table*,unsigned int) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_pool_alloc ; 
 scalar_t__ unlikely (int) ; 

int sg_alloc_table_chained(struct sg_table *table, int nents,
		struct scatterlist *first_chunk, unsigned nents_first_chunk)
{
	int ret;

	BUG_ON(!nents);

	if (first_chunk && nents_first_chunk) {
		if (nents <= nents_first_chunk) {
			table->nents = table->orig_nents = nents;
			sg_init_table(table->sgl, nents);
			return 0;
		}
	}

	/* User supposes that the 1st SGL includes real entry */
	if (nents_first_chunk <= 1) {
		first_chunk = NULL;
		nents_first_chunk = 0;
	}

	ret = __sg_alloc_table(table, nents, SG_CHUNK_SIZE,
			       first_chunk, nents_first_chunk,
			       GFP_ATOMIC, sg_pool_alloc);
	if (unlikely(ret))
		sg_free_table_chained(table, nents_first_chunk);
	return ret;
}