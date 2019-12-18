#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
struct mem_cgroup {int /*<<< orphan*/  css; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_5__ {scalar_t__ mem_cgroup; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 TYPE_3__* compound_head (struct page*) ; 
 int /*<<< orphan*/  css_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  css_tryget_online (int /*<<< orphan*/ *) ; 
 scalar_t__ do_swap_account ; 
 struct mem_cgroup* get_mem_cgroup_from_mm (struct mm_struct*) ; 
 int hpage_nr_pages (struct page*) ; 
 unsigned short lookup_swap_cgroup_id (TYPE_1__) ; 
 scalar_t__ mem_cgroup_disabled () ; 
 struct mem_cgroup* mem_cgroup_from_id (unsigned short) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int try_charge (struct mem_cgroup*,int /*<<< orphan*/ ,unsigned int) ; 

int mem_cgroup_try_charge(struct page *page, struct mm_struct *mm,
			  gfp_t gfp_mask, struct mem_cgroup **memcgp,
			  bool compound)
{
	struct mem_cgroup *memcg = NULL;
	unsigned int nr_pages = compound ? hpage_nr_pages(page) : 1;
	int ret = 0;

	if (mem_cgroup_disabled())
		goto out;

	if (PageSwapCache(page)) {
		/*
		 * Every swap fault against a single page tries to charge the
		 * page, bail as early as possible.  shmem_unuse() encounters
		 * already charged pages, too.  The USED bit is protected by
		 * the page lock, which serializes swap cache removal, which
		 * in turn serializes uncharging.
		 */
		VM_BUG_ON_PAGE(!PageLocked(page), page);
		if (compound_head(page)->mem_cgroup)
			goto out;

		if (do_swap_account) {
			swp_entry_t ent = { .val = page_private(page), };
			unsigned short id = lookup_swap_cgroup_id(ent);

			rcu_read_lock();
			memcg = mem_cgroup_from_id(id);
			if (memcg && !css_tryget_online(&memcg->css))
				memcg = NULL;
			rcu_read_unlock();
		}
	}

	if (!memcg)
		memcg = get_mem_cgroup_from_mm(mm);

	ret = try_charge(memcg, gfp_mask, nr_pages);

	css_put(&memcg->css);
out:
	*memcgp = memcg;
	return ret;
}