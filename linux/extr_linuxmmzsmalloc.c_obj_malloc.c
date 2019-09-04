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
struct zspage {TYPE_1__* first_page; } ;
struct size_class {unsigned long size; } ;
struct page {int dummy; } ;
struct link_free {int next; unsigned long handle; } ;
struct TYPE_2__ {unsigned long index; } ;

/* Variables and functions */
 unsigned long OBJ_ALLOCATED_TAG ; 
 int OBJ_TAG_BITS ; 
 int /*<<< orphan*/  OBJ_USED ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PageHugeObject (struct page*) ; 
 struct page* get_first_page (struct zspage*) ; 
 unsigned long get_freeobj (struct zspage*) ; 
 struct page* get_next_page (struct page*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 scalar_t__ likely (int) ; 
 unsigned long location_to_obj (struct page*,unsigned long) ; 
 int /*<<< orphan*/  mod_zspage_inuse (struct zspage*,int) ; 
 int /*<<< orphan*/  set_freeobj (struct zspage*,int) ; 
 int /*<<< orphan*/  zs_stat_inc (struct size_class*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned long obj_malloc(struct size_class *class,
				struct zspage *zspage, unsigned long handle)
{
	int i, nr_page, offset;
	unsigned long obj;
	struct link_free *link;

	struct page *m_page;
	unsigned long m_offset;
	void *vaddr;

	handle |= OBJ_ALLOCATED_TAG;
	obj = get_freeobj(zspage);

	offset = obj * class->size;
	nr_page = offset >> PAGE_SHIFT;
	m_offset = offset & ~PAGE_MASK;
	m_page = get_first_page(zspage);

	for (i = 0; i < nr_page; i++)
		m_page = get_next_page(m_page);

	vaddr = kmap_atomic(m_page);
	link = (struct link_free *)vaddr + m_offset / sizeof(*link);
	set_freeobj(zspage, link->next >> OBJ_TAG_BITS);
	if (likely(!PageHugeObject(m_page)))
		/* record handle in the header of allocated chunk */
		link->handle = handle;
	else
		/* record handle to page->index */
		zspage->first_page->index = handle;

	kunmap_atomic(vaddr);
	mod_zspage_inuse(zspage, 1);
	zs_stat_inc(class, OBJ_USED, 1);

	obj = location_to_obj(m_page, obj);

	return obj;
}