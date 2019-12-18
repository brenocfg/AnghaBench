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
struct lru_cache {unsigned int nr_elements; struct lc_element** lc_element; } ;
struct lc_element {unsigned int lc_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

struct lc_element *lc_element_by_index(struct lru_cache *lc, unsigned i)
{
	BUG_ON(i >= lc->nr_elements);
	BUG_ON(lc->lc_element[i] == NULL);
	BUG_ON(lc->lc_element[i]->lc_index != i);
	return lc->lc_element[i];
}