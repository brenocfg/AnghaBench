#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crush_work_bucket {int dummy; } ;
struct crush_work {TYPE_1__** work; } ;
struct crush_map {int max_buckets; int working_size; TYPE_2__** buckets; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  size_t __s32 ;
struct TYPE_4__ {int alg; int size; } ;
struct TYPE_3__ {void* perm; scalar_t__ perm_n; scalar_t__ perm_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

void crush_init_workspace(const struct crush_map *map, void *v)
{
	struct crush_work *w = v;
	__s32 b;

	/*
	 * We work by moving through the available space and setting
	 * values and pointers as we go.
	 *
	 * It's a bit like Forth's use of the 'allot' word since we
	 * set the pointer first and then reserve the space for it to
	 * point to by incrementing the point.
	 */
	v += sizeof(struct crush_work);
	w->work = v;
	v += map->max_buckets * sizeof(struct crush_work_bucket *);
	for (b = 0; b < map->max_buckets; ++b) {
		if (!map->buckets[b])
			continue;

		w->work[b] = v;
		switch (map->buckets[b]->alg) {
		default:
			v += sizeof(struct crush_work_bucket);
			break;
		}
		w->work[b]->perm_x = 0;
		w->work[b]->perm_n = 0;
		w->work[b]->perm = v;
		v += map->buckets[b]->size * sizeof(__u32);
	}
	BUG_ON(v - (void *)w != map->working_size);
}