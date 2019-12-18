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
struct crush_work {int /*<<< orphan*/ * work; } ;
struct crush_map {int max_devices; int max_buckets; unsigned int choose_total_tries; int /*<<< orphan*/ * choose_tries; struct crush_bucket** buckets; } ;
struct crush_choose_arg {int dummy; } ;
struct crush_bucket {int id; int size; int type; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int bucket_perm_choose (struct crush_bucket const*,int /*<<< orphan*/ ,int,int) ; 
 int crush_bucket_choose (struct crush_bucket const*,int /*<<< orphan*/ ,int,int,struct crush_choose_arg const*,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int is_out (struct crush_map const*,int /*<<< orphan*/  const*,int,int,int) ; 

__attribute__((used)) static int crush_choose_firstn(const struct crush_map *map,
			       struct crush_work *work,
			       const struct crush_bucket *bucket,
			       const __u32 *weight, int weight_max,
			       int x, int numrep, int type,
			       int *out, int outpos,
			       int out_size,
			       unsigned int tries,
			       unsigned int recurse_tries,
			       unsigned int local_retries,
			       unsigned int local_fallback_retries,
			       int recurse_to_leaf,
			       unsigned int vary_r,
			       unsigned int stable,
			       int *out2,
			       int parent_r,
			       const struct crush_choose_arg *choose_args)
{
	int rep;
	unsigned int ftotal, flocal;
	int retry_descent, retry_bucket, skip_rep;
	const struct crush_bucket *in = bucket;
	int r;
	int i;
	int item = 0;
	int itemtype;
	int collide, reject;
	int count = out_size;

	dprintk("CHOOSE%s bucket %d x %d outpos %d numrep %d tries %d recurse_tries %d local_retries %d local_fallback_retries %d parent_r %d stable %d\n",
		recurse_to_leaf ? "_LEAF" : "",
		bucket->id, x, outpos, numrep,
		tries, recurse_tries, local_retries, local_fallback_retries,
		parent_r, stable);

	for (rep = stable ? 0 : outpos; rep < numrep && count > 0 ; rep++) {
		/* keep trying until we get a non-out, non-colliding item */
		ftotal = 0;
		skip_rep = 0;
		do {
			retry_descent = 0;
			in = bucket;               /* initial bucket */

			/* choose through intervening buckets */
			flocal = 0;
			do {
				collide = 0;
				retry_bucket = 0;
				r = rep + parent_r;
				/* r' = r + f_total */
				r += ftotal;

				/* bucket choose */
				if (in->size == 0) {
					reject = 1;
					goto reject;
				}
				if (local_fallback_retries > 0 &&
				    flocal >= (in->size>>1) &&
				    flocal > local_fallback_retries)
					item = bucket_perm_choose(
						in, work->work[-1-in->id],
						x, r);
				else
					item = crush_bucket_choose(
						in, work->work[-1-in->id],
						x, r,
						(choose_args ?
						 &choose_args[-1-in->id] : NULL),
						outpos);
				if (item >= map->max_devices) {
					dprintk("   bad item %d\n", item);
					skip_rep = 1;
					break;
				}

				/* desired type? */
				if (item < 0)
					itemtype = map->buckets[-1-item]->type;
				else
					itemtype = 0;
				dprintk("  item %d type %d\n", item, itemtype);

				/* keep going? */
				if (itemtype != type) {
					if (item >= 0 ||
					    (-1-item) >= map->max_buckets) {
						dprintk("   bad item type %d\n", type);
						skip_rep = 1;
						break;
					}
					in = map->buckets[-1-item];
					retry_bucket = 1;
					continue;
				}

				/* collision? */
				for (i = 0; i < outpos; i++) {
					if (out[i] == item) {
						collide = 1;
						break;
					}
				}

				reject = 0;
				if (!collide && recurse_to_leaf) {
					if (item < 0) {
						int sub_r;
						if (vary_r)
							sub_r = r >> (vary_r-1);
						else
							sub_r = 0;
						if (crush_choose_firstn(
							    map,
							    work,
							    map->buckets[-1-item],
							    weight, weight_max,
							    x, stable ? 1 : outpos+1, 0,
							    out2, outpos, count,
							    recurse_tries, 0,
							    local_retries,
							    local_fallback_retries,
							    0,
							    vary_r,
							    stable,
							    NULL,
							    sub_r,
							    choose_args) <= outpos)
							/* didn't get leaf */
							reject = 1;
					} else {
						/* we already have a leaf! */
						out2[outpos] = item;
					}
				}

				if (!reject && !collide) {
					/* out? */
					if (itemtype == 0)
						reject = is_out(map, weight,
								weight_max,
								item, x);
				}

reject:
				if (reject || collide) {
					ftotal++;
					flocal++;

					if (collide && flocal <= local_retries)
						/* retry locally a few times */
						retry_bucket = 1;
					else if (local_fallback_retries > 0 &&
						 flocal <= in->size + local_fallback_retries)
						/* exhaustive bucket search */
						retry_bucket = 1;
					else if (ftotal < tries)
						/* then retry descent */
						retry_descent = 1;
					else
						/* else give up */
						skip_rep = 1;
					dprintk("  reject %d  collide %d  "
						"ftotal %u  flocal %u\n",
						reject, collide, ftotal,
						flocal);
				}
			} while (retry_bucket);
		} while (retry_descent);

		if (skip_rep) {
			dprintk("skip rep\n");
			continue;
		}

		dprintk("CHOOSE got %d\n", item);
		out[outpos] = item;
		outpos++;
		count--;
#ifndef __KERNEL__
		if (map->choose_tries && ftotal <= map->choose_total_tries)
			map->choose_tries[ftotal]++;
#endif
	}

	dprintk("CHOOSE returns %d\n", outpos);
	return outpos;
}