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
struct zspage {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pages_compacted; } ;
struct zs_pool {TYPE_1__ stats; } ;
struct zs_compact_control {void* d_page; void* s_page; scalar_t__ obj_idx; } ;
struct size_class {int /*<<< orphan*/  lock; scalar_t__ pages_per_zspage; } ;

/* Variables and functions */
 scalar_t__ ZS_EMPTY ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  free_zspage (struct zs_pool*,struct size_class*,struct zspage*) ; 
 void* get_first_page (struct zspage*) ; 
 struct zspage* isolate_zspage (struct size_class*,int) ; 
 int /*<<< orphan*/  migrate_zspage (struct zs_pool*,struct size_class*,struct zs_compact_control*) ; 
 scalar_t__ putback_zspage (struct size_class*,struct zspage*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zs_can_compact (struct size_class*) ; 

__attribute__((used)) static void __zs_compact(struct zs_pool *pool, struct size_class *class)
{
	struct zs_compact_control cc;
	struct zspage *src_zspage;
	struct zspage *dst_zspage = NULL;

	spin_lock(&class->lock);
	while ((src_zspage = isolate_zspage(class, true))) {

		if (!zs_can_compact(class))
			break;

		cc.obj_idx = 0;
		cc.s_page = get_first_page(src_zspage);

		while ((dst_zspage = isolate_zspage(class, false))) {
			cc.d_page = get_first_page(dst_zspage);
			/*
			 * If there is no more space in dst_page, resched
			 * and see if anyone had allocated another zspage.
			 */
			if (!migrate_zspage(pool, class, &cc))
				break;

			putback_zspage(class, dst_zspage);
		}

		/* Stop if we couldn't find slot */
		if (dst_zspage == NULL)
			break;

		putback_zspage(class, dst_zspage);
		if (putback_zspage(class, src_zspage) == ZS_EMPTY) {
			free_zspage(pool, class, src_zspage);
			pool->stats.pages_compacted += class->pages_per_zspage;
		}
		spin_unlock(&class->lock);
		cond_resched();
		spin_lock(&class->lock);
	}

	if (src_zspage)
		putback_zspage(class, src_zspage);

	spin_unlock(&class->lock);
}