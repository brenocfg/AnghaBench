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
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct ion_buffer {int flags; struct sg_table* sg_table; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int ION_FLAG_CACHED ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int ion_heap_sglist_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 

int ion_heap_buffer_zero(struct ion_buffer *buffer)
{
	struct sg_table *table = buffer->sg_table;
	pgprot_t pgprot;

	if (buffer->flags & ION_FLAG_CACHED)
		pgprot = PAGE_KERNEL;
	else
		pgprot = pgprot_writecombine(PAGE_KERNEL);

	return ion_heap_sglist_zero(table->sgl, table->nents, pgprot);
}