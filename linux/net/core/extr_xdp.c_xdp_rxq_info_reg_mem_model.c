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
struct TYPE_2__ {int type; int id; } ;
struct xdp_rxq_info {scalar_t__ reg_state; TYPE_1__ mem; } ;
struct xdp_mem_allocator {int /*<<< orphan*/  page_pool; int /*<<< orphan*/  node; void* allocator; TYPE_1__ mem; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum xdp_mem_type { ____Placeholder_xdp_mem_type } xdp_mem_type ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int MEM_TYPE_PAGE_POOL ; 
 int MEM_TYPE_ZERO_COPY ; 
 int PTR_ERR (void*) ; 
 scalar_t__ REG_STATE_REGISTERED ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __is_supported_mem_type (int) ; 
 int __mem_id_cyclic_get (int /*<<< orphan*/ ) ; 
 int __mem_id_init_hash_table () ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct xdp_mem_allocator*) ; 
 struct xdp_mem_allocator* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_id_ht ; 
 int /*<<< orphan*/  mem_id_init ; 
 int /*<<< orphan*/  mem_id_lock ; 
 int /*<<< orphan*/  mem_id_pool ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_pool_get (int /*<<< orphan*/ ) ; 
 void* rhashtable_insert_slow (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mem_connect (struct xdp_mem_allocator*,struct xdp_rxq_info*) ; 

int xdp_rxq_info_reg_mem_model(struct xdp_rxq_info *xdp_rxq,
			       enum xdp_mem_type type, void *allocator)
{
	struct xdp_mem_allocator *xdp_alloc;
	gfp_t gfp = GFP_KERNEL;
	int id, errno, ret;
	void *ptr;

	if (xdp_rxq->reg_state != REG_STATE_REGISTERED) {
		WARN(1, "Missing register, driver bug");
		return -EFAULT;
	}

	if (!__is_supported_mem_type(type))
		return -EOPNOTSUPP;

	xdp_rxq->mem.type = type;

	if (!allocator) {
		if (type == MEM_TYPE_PAGE_POOL || type == MEM_TYPE_ZERO_COPY)
			return -EINVAL; /* Setup time check page_pool req */
		return 0;
	}

	/* Delay init of rhashtable to save memory if feature isn't used */
	if (!mem_id_init) {
		mutex_lock(&mem_id_lock);
		ret = __mem_id_init_hash_table();
		mutex_unlock(&mem_id_lock);
		if (ret < 0) {
			WARN_ON(1);
			return ret;
		}
	}

	xdp_alloc = kzalloc(sizeof(*xdp_alloc), gfp);
	if (!xdp_alloc)
		return -ENOMEM;

	mutex_lock(&mem_id_lock);
	id = __mem_id_cyclic_get(gfp);
	if (id < 0) {
		errno = id;
		goto err;
	}
	xdp_rxq->mem.id = id;
	xdp_alloc->mem  = xdp_rxq->mem;
	xdp_alloc->allocator = allocator;

	/* Insert allocator into ID lookup table */
	ptr = rhashtable_insert_slow(mem_id_ht, &id, &xdp_alloc->node);
	if (IS_ERR(ptr)) {
		ida_simple_remove(&mem_id_pool, xdp_rxq->mem.id);
		xdp_rxq->mem.id = 0;
		errno = PTR_ERR(ptr);
		goto err;
	}

	if (type == MEM_TYPE_PAGE_POOL)
		page_pool_get(xdp_alloc->page_pool);

	mutex_unlock(&mem_id_lock);

	trace_mem_connect(xdp_alloc, xdp_rxq);
	return 0;
err:
	mutex_unlock(&mem_id_lock);
	kfree(xdp_alloc);
	return errno;
}