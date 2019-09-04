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
struct cma_mem {int n; int p; } ;
struct cma {scalar_t__ order_per_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  cma_add_to_cma_mem_list (struct cma*,struct cma_mem*) ; 
 struct cma_mem* cma_get_entry_from_list (struct cma*) ; 
 int /*<<< orphan*/  cma_release (struct cma*,int,int) ; 
 int /*<<< orphan*/  kfree (struct cma_mem*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int cma_free_mem(struct cma *cma, int count)
{
	struct cma_mem *mem = NULL;

	while (count) {
		mem = cma_get_entry_from_list(cma);
		if (mem == NULL)
			return 0;

		if (mem->n <= count) {
			cma_release(cma, mem->p, mem->n);
			count -= mem->n;
			kfree(mem);
		} else if (cma->order_per_bit == 0) {
			cma_release(cma, mem->p, count);
			mem->p += count;
			mem->n -= count;
			count = 0;
			cma_add_to_cma_mem_list(cma, mem);
		} else {
			pr_debug("cma: cannot release partial block when order_per_bit != 0\n");
			cma_add_to_cma_mem_list(cma, mem);
			break;
		}
	}

	return 0;

}