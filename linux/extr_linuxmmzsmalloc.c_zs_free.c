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
struct zs_pool {struct size_class** size_class; } ;
struct size_class {int /*<<< orphan*/  lock; } ;
struct page {int dummy; } ;
typedef  enum fullness_group { ____Placeholder_fullness_group } fullness_group ;

/* Variables and functions */
 int ZS_EMPTY ; 
 int /*<<< orphan*/  cache_free_handle (struct zs_pool*,unsigned long) ; 
 int fix_fullness_group (struct size_class*,struct zspage*) ; 
 int /*<<< orphan*/  free_zspage (struct zs_pool*,struct size_class*,struct zspage*) ; 
 struct zspage* get_zspage (struct page*) ; 
 int /*<<< orphan*/  get_zspage_mapping (struct zspage*,int*,int*) ; 
 unsigned long handle_to_obj (unsigned long) ; 
 int is_zspage_isolated (struct zspage*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  migrate_read_lock (struct zspage*) ; 
 int /*<<< orphan*/  migrate_read_unlock (struct zspage*) ; 
 int /*<<< orphan*/  obj_free (struct size_class*,unsigned long) ; 
 int /*<<< orphan*/  obj_to_location (unsigned long,struct page**,unsigned int*) ; 
 int /*<<< orphan*/  pin_tag (unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unpin_tag (unsigned long) ; 

void zs_free(struct zs_pool *pool, unsigned long handle)
{
	struct zspage *zspage;
	struct page *f_page;
	unsigned long obj;
	unsigned int f_objidx;
	int class_idx;
	struct size_class *class;
	enum fullness_group fullness;
	bool isolated;

	if (unlikely(!handle))
		return;

	pin_tag(handle);
	obj = handle_to_obj(handle);
	obj_to_location(obj, &f_page, &f_objidx);
	zspage = get_zspage(f_page);

	migrate_read_lock(zspage);

	get_zspage_mapping(zspage, &class_idx, &fullness);
	class = pool->size_class[class_idx];

	spin_lock(&class->lock);
	obj_free(class, obj);
	fullness = fix_fullness_group(class, zspage);
	if (fullness != ZS_EMPTY) {
		migrate_read_unlock(zspage);
		goto out;
	}

	isolated = is_zspage_isolated(zspage);
	migrate_read_unlock(zspage);
	/* If zspage is isolated, zs_page_putback will free the zspage */
	if (likely(!isolated))
		free_zspage(pool, class, zspage);
out:

	spin_unlock(&class->lock);
	unpin_tag(handle);
	cache_free_handle(pool, handle);
}