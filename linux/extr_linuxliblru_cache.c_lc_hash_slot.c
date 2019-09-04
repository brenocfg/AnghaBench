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
struct lru_cache {unsigned int nr_elements; struct hlist_head* lc_slot; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct hlist_head *lc_hash_slot(struct lru_cache *lc, unsigned int enr)
{
	return  lc->lc_slot + (enr % lc->nr_elements);
}