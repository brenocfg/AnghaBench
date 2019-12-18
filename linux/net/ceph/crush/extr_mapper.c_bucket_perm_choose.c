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
struct crush_work_bucket {int perm_x; int perm_n; unsigned int* perm; } ;
struct crush_bucket {int size; int* items; int /*<<< orphan*/  id; int /*<<< orphan*/  hash; } ;
typedef  int __u32 ;

/* Variables and functions */
 unsigned int crush_hash32_3 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dprintk (char*,unsigned int,unsigned int,...) ; 

__attribute__((used)) static int bucket_perm_choose(const struct crush_bucket *bucket,
			      struct crush_work_bucket *work,
			      int x, int r)
{
	unsigned int pr = r % bucket->size;
	unsigned int i, s;

	/* start a new permutation if @x has changed */
	if (work->perm_x != (__u32)x || work->perm_n == 0) {
		dprintk("bucket %d new x=%d\n", bucket->id, x);
		work->perm_x = x;

		/* optimize common r=0 case */
		if (pr == 0) {
			s = crush_hash32_3(bucket->hash, x, bucket->id, 0) %
				bucket->size;
			work->perm[0] = s;
			work->perm_n = 0xffff;   /* magic value, see below */
			goto out;
		}

		for (i = 0; i < bucket->size; i++)
			work->perm[i] = i;
		work->perm_n = 0;
	} else if (work->perm_n == 0xffff) {
		/* clean up after the r=0 case above */
		for (i = 1; i < bucket->size; i++)
			work->perm[i] = i;
		work->perm[work->perm[0]] = 0;
		work->perm_n = 1;
	}

	/* calculate permutation up to pr */
	for (i = 0; i < work->perm_n; i++)
		dprintk(" perm_choose have %d: %d\n", i, work->perm[i]);
	while (work->perm_n <= pr) {
		unsigned int p = work->perm_n;
		/* no point in swapping the final entry */
		if (p < bucket->size - 1) {
			i = crush_hash32_3(bucket->hash, x, bucket->id, p) %
				(bucket->size - p);
			if (i) {
				unsigned int t = work->perm[p + i];
				work->perm[p + i] = work->perm[p];
				work->perm[p] = t;
			}
			dprintk(" perm_choose swap %d with %d\n", p, p+i);
		}
		work->perm_n++;
	}
	for (i = 0; i < bucket->size; i++)
		dprintk(" perm_choose  %d: %d\n", i, work->perm[i]);

	s = work->perm[pr];
out:
	dprintk(" perm_choose %d sz=%d x=%d r=%d (%d) s=%d\n", bucket->id,
		bucket->size, x, r, pr, s);
	return bucket->items[s];
}