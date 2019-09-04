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
struct sg_table {scalar_t__ orig_nents; } ;

/* Variables and functions */
 scalar_t__ SG_CHUNK_SIZE ; 
 int /*<<< orphan*/  __sg_free_table (struct sg_table*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_pool_free ; 

void sg_free_table_chained(struct sg_table *table, bool first_chunk)
{
	if (first_chunk && table->orig_nents <= SG_CHUNK_SIZE)
		return;
	__sg_free_table(table, SG_CHUNK_SIZE, first_chunk, sg_pool_free);
}