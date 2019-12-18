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
struct lru_cache {int /*<<< orphan*/  lc_cache; int /*<<< orphan*/  element_off; void** lc_element; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void lc_free_by_index(struct lru_cache *lc, unsigned i)
{
	void *p = lc->lc_element[i];
	WARN_ON(!p);
	if (p) {
		p -= lc->element_off;
		kmem_cache_free(lc->lc_cache, p);
	}
}