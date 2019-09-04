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
struct tee_shm_pool_mgr {struct gen_pool* private_data; } ;
struct tee_shm {size_t size; int /*<<< orphan*/  paddr; void* kaddr; } ;
struct gen_pool {int min_alloc_order; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long gen_pool_alloc (struct gen_pool*,size_t) ; 
 int /*<<< orphan*/  gen_pool_virt_to_phys (struct gen_pool*,unsigned long) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 size_t roundup (size_t,int) ; 

__attribute__((used)) static int pool_op_gen_alloc(struct tee_shm_pool_mgr *poolm,
			     struct tee_shm *shm, size_t size)
{
	unsigned long va;
	struct gen_pool *genpool = poolm->private_data;
	size_t s = roundup(size, 1 << genpool->min_alloc_order);

	va = gen_pool_alloc(genpool, s);
	if (!va)
		return -ENOMEM;

	memset((void *)va, 0, s);
	shm->kaddr = (void *)va;
	shm->paddr = gen_pool_virt_to_phys(genpool, va);
	shm->size = s;
	return 0;
}