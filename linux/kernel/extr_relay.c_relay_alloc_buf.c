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
struct rchan_buf {unsigned int page_count; int /*<<< orphan*/ * page_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PAGE_ALIGN (size_t) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_MAP ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * relay_alloc_page_array (unsigned int) ; 
 int /*<<< orphan*/  relay_free_page_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_private (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 void* vmap (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *relay_alloc_buf(struct rchan_buf *buf, size_t *size)
{
	void *mem;
	unsigned int i, j, n_pages;

	*size = PAGE_ALIGN(*size);
	n_pages = *size >> PAGE_SHIFT;

	buf->page_array = relay_alloc_page_array(n_pages);
	if (!buf->page_array)
		return NULL;

	for (i = 0; i < n_pages; i++) {
		buf->page_array[i] = alloc_page(GFP_KERNEL);
		if (unlikely(!buf->page_array[i]))
			goto depopulate;
		set_page_private(buf->page_array[i], (unsigned long)buf);
	}
	mem = vmap(buf->page_array, n_pages, VM_MAP, PAGE_KERNEL);
	if (!mem)
		goto depopulate;

	memset(mem, 0, *size);
	buf->page_count = n_pages;
	return mem;

depopulate:
	for (j = 0; j < i; j++)
		__free_page(buf->page_array[j]);
	relay_free_page_array(buf->page_array);
	return NULL;
}