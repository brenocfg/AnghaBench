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
struct xdp_mem_info {int type; int /*<<< orphan*/  id; } ;
struct xdp_mem_allocator {TYPE_1__* zc_alloc; int /*<<< orphan*/  page_pool; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (TYPE_1__*,unsigned long) ;} ;

/* Variables and functions */
#define  MEM_TYPE_PAGE_ORDER0 131 
#define  MEM_TYPE_PAGE_POOL 130 
#define  MEM_TYPE_PAGE_SHARED 129 
#define  MEM_TYPE_ZERO_COPY 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  likely (struct xdp_mem_allocator*) ; 
 int /*<<< orphan*/  mem_id_ht ; 
 int /*<<< orphan*/  mem_id_rht_params ; 
 int /*<<< orphan*/  page_frag_free (void*) ; 
 int /*<<< orphan*/  page_pool_put_page (int /*<<< orphan*/ ,struct page*,int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct xdp_mem_allocator* rhashtable_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  trace_mem_return_failed (struct xdp_mem_info*,struct page*) ; 
 struct page* virt_to_head_page (void*) ; 
 struct page* virt_to_page (void*) ; 
 int /*<<< orphan*/  xdp_return_frame_no_direct () ; 

__attribute__((used)) static void __xdp_return(void *data, struct xdp_mem_info *mem, bool napi_direct,
			 unsigned long handle)
{
	struct xdp_mem_allocator *xa;
	struct page *page;

	switch (mem->type) {
	case MEM_TYPE_PAGE_POOL:
		rcu_read_lock();
		/* mem->id is valid, checked in xdp_rxq_info_reg_mem_model() */
		xa = rhashtable_lookup(mem_id_ht, &mem->id, mem_id_rht_params);
		page = virt_to_head_page(data);
		if (likely(xa)) {
			napi_direct &= !xdp_return_frame_no_direct();
			page_pool_put_page(xa->page_pool, page, napi_direct);
		} else {
			/* Hopefully stack show who to blame for late return */
			WARN_ONCE(1, "page_pool gone mem.id=%d", mem->id);
			trace_mem_return_failed(mem, page);
			put_page(page);
		}
		rcu_read_unlock();
		break;
	case MEM_TYPE_PAGE_SHARED:
		page_frag_free(data);
		break;
	case MEM_TYPE_PAGE_ORDER0:
		page = virt_to_page(data); /* Assumes order0 page*/
		put_page(page);
		break;
	case MEM_TYPE_ZERO_COPY:
		/* NB! Only valid from an xdp_buff! */
		rcu_read_lock();
		/* mem->id is valid, checked in xdp_rxq_info_reg_mem_model() */
		xa = rhashtable_lookup(mem_id_ht, &mem->id, mem_id_rht_params);
		xa->zc_alloc->free(xa->zc_alloc, handle);
		rcu_read_unlock();
	default:
		/* Not possible, checked in xdp_rxq_info_reg_mem_model() */
		break;
	}
}