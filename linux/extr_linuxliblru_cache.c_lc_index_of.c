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
struct lru_cache {int dummy; } ;
struct lc_element {unsigned int lc_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARANOIA_LC_ELEMENT (struct lru_cache*,struct lc_element*) ; 

unsigned int lc_index_of(struct lru_cache *lc, struct lc_element *e)
{
	PARANOIA_LC_ELEMENT(lc, e);
	return e->lc_index;
}