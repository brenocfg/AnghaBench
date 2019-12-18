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
struct xdp_mem_info {int /*<<< orphan*/  id; } ;
struct xdp_mem_allocator {int /*<<< orphan*/  page_pool; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mem_id_ht ; 
 int /*<<< orphan*/  mem_id_rht_params ; 
 int /*<<< orphan*/  page_pool_release_page (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct xdp_mem_allocator* rhashtable_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct page* virt_to_head_page (void*) ; 

void __xdp_release_frame(void *data, struct xdp_mem_info *mem)
{
	struct xdp_mem_allocator *xa;
	struct page *page;

	rcu_read_lock();
	xa = rhashtable_lookup(mem_id_ht, &mem->id, mem_id_rht_params);
	page = virt_to_head_page(data);
	if (xa)
		page_pool_release_page(xa->page_pool, page);
	rcu_read_unlock();
}