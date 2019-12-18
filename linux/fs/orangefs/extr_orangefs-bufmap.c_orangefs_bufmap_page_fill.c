#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct orangefs_bufmap_desc {int /*<<< orphan*/ * page_array; } ;
struct TYPE_2__ {struct orangefs_bufmap_desc* desc_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_1__* __orangefs_bufmap ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

void orangefs_bufmap_page_fill(void *page_to,
				int buffer_index,
				int slot_index)
{
	struct orangefs_bufmap_desc *from;
	void *page_from;

	from = &__orangefs_bufmap->desc_array[buffer_index];
	page_from = kmap_atomic(from->page_array[slot_index]);
	memcpy(page_to, page_from, PAGE_SIZE);
	kunmap_atomic(page_from);
}