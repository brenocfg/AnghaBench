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
struct zs_pool {int dummy; } ;
struct zs_compact_control {int obj_idx; struct page* s_page; struct page* d_page; } ;
struct size_class {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 unsigned long BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HANDLE_PIN_BIT ; 
 unsigned long find_alloced_obj (struct size_class*,struct page*,int*) ; 
 struct page* get_next_page (struct page*) ; 
 int /*<<< orphan*/  get_zspage (struct page*) ; 
 unsigned long handle_to_obj (unsigned long) ; 
 int /*<<< orphan*/  obj_free (struct size_class*,unsigned long) ; 
 unsigned long obj_malloc (struct size_class*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  record_obj (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  unpin_tag (unsigned long) ; 
 int /*<<< orphan*/  zs_object_copy (struct size_class*,unsigned long,unsigned long) ; 
 scalar_t__ zspage_full (struct size_class*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int migrate_zspage(struct zs_pool *pool, struct size_class *class,
				struct zs_compact_control *cc)
{
	unsigned long used_obj, free_obj;
	unsigned long handle;
	struct page *s_page = cc->s_page;
	struct page *d_page = cc->d_page;
	int obj_idx = cc->obj_idx;
	int ret = 0;

	while (1) {
		handle = find_alloced_obj(class, s_page, &obj_idx);
		if (!handle) {
			s_page = get_next_page(s_page);
			if (!s_page)
				break;
			obj_idx = 0;
			continue;
		}

		/* Stop if there is no more space */
		if (zspage_full(class, get_zspage(d_page))) {
			unpin_tag(handle);
			ret = -ENOMEM;
			break;
		}

		used_obj = handle_to_obj(handle);
		free_obj = obj_malloc(class, get_zspage(d_page), handle);
		zs_object_copy(class, free_obj, used_obj);
		obj_idx++;
		/*
		 * record_obj updates handle's value to free_obj and it will
		 * invalidate lock bit(ie, HANDLE_PIN_BIT) of handle, which
		 * breaks synchronization using pin_tag(e,g, zs_free) so
		 * let's keep the lock bit.
		 */
		free_obj |= BIT(HANDLE_PIN_BIT);
		record_obj(handle, free_obj);
		unpin_tag(handle);
		obj_free(class, used_obj);
	}

	/* Remember last position in this iteration */
	cc->s_page = s_page;
	cc->obj_idx = obj_idx;

	return ret;
}