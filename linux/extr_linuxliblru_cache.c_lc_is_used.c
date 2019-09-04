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
struct lc_element {scalar_t__ refcnt; } ;

/* Variables and functions */
 struct lc_element* __lc_find (struct lru_cache*,unsigned int,int) ; 

bool lc_is_used(struct lru_cache *lc, unsigned int enr)
{
	struct lc_element *e = __lc_find(lc, enr, 1);
	return e && e->refcnt;
}