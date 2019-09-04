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
struct crush_work_bucket {int dummy; } ;
struct crush_work {int dummy; } ;
struct crush_map {int working_size; int max_buckets; TYPE_1__** buckets; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  size_t __s32 ;
struct TYPE_2__ {int alg; int size; } ;

/* Variables and functions */

__attribute__((used)) static void crush_finalize(struct crush_map *c)
{
	__s32 b;

	/* Space for the array of pointers to per-bucket workspace */
	c->working_size = sizeof(struct crush_work) +
	    c->max_buckets * sizeof(struct crush_work_bucket *);

	for (b = 0; b < c->max_buckets; b++) {
		if (!c->buckets[b])
			continue;

		switch (c->buckets[b]->alg) {
		default:
			/*
			 * The base case, permutation variables and
			 * the pointer to the permutation array.
			 */
			c->working_size += sizeof(struct crush_work_bucket);
			break;
		}
		/* Every bucket has a permutation array. */
		c->working_size += c->buckets[b]->size * sizeof(__u32);
	}
}