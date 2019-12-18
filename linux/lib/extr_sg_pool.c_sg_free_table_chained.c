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
struct sg_table {unsigned int orig_nents; } ;

/* Variables and functions */
 int /*<<< orphan*/  SG_CHUNK_SIZE ; 
 int /*<<< orphan*/  __sg_free_table (struct sg_table*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_pool_free ; 

void sg_free_table_chained(struct sg_table *table,
		unsigned nents_first_chunk)
{
	if (table->orig_nents <= nents_first_chunk)
		return;

	if (nents_first_chunk == 1)
		nents_first_chunk = 0;

	__sg_free_table(table, SG_CHUNK_SIZE, nents_first_chunk, sg_pool_free);
}