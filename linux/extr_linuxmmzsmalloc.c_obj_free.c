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
struct zspage {int dummy; } ;
struct size_class {unsigned int size; } ;
struct page {int dummy; } ;
struct link_free {int next; } ;

/* Variables and functions */
 unsigned long OBJ_ALLOCATED_TAG ; 
 int OBJ_TAG_BITS ; 
 int /*<<< orphan*/  OBJ_USED ; 
 unsigned int PAGE_MASK ; 
 int get_freeobj (struct zspage*) ; 
 struct zspage* get_zspage (struct page*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  mod_zspage_inuse (struct zspage*,int) ; 
 int /*<<< orphan*/  obj_to_location (unsigned long,struct page**,unsigned int*) ; 
 int /*<<< orphan*/  set_freeobj (struct zspage*,unsigned int) ; 
 int /*<<< orphan*/  zs_stat_dec (struct size_class*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void obj_free(struct size_class *class, unsigned long obj)
{
	struct link_free *link;
	struct zspage *zspage;
	struct page *f_page;
	unsigned long f_offset;
	unsigned int f_objidx;
	void *vaddr;

	obj &= ~OBJ_ALLOCATED_TAG;
	obj_to_location(obj, &f_page, &f_objidx);
	f_offset = (class->size * f_objidx) & ~PAGE_MASK;
	zspage = get_zspage(f_page);

	vaddr = kmap_atomic(f_page);

	/* Insert this object in containing zspage's freelist */
	link = (struct link_free *)(vaddr + f_offset);
	link->next = get_freeobj(zspage) << OBJ_TAG_BITS;
	kunmap_atomic(vaddr);
	set_freeobj(zspage, f_objidx);
	mod_zspage_inuse(zspage, -1);
	zs_stat_dec(class, OBJ_USED, 1);
}