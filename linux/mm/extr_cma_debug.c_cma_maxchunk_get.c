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
typedef  int u64 ;
struct cma {int order_per_bit; int /*<<< orphan*/  lock; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 unsigned long cma_bitmap_maxno (struct cma*) ; 
 unsigned long find_next_bit (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 unsigned long find_next_zero_bit (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 unsigned long max (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cma_maxchunk_get(void *data, u64 *val)
{
	struct cma *cma = data;
	unsigned long maxchunk = 0;
	unsigned long start, end = 0;
	unsigned long bitmap_maxno = cma_bitmap_maxno(cma);

	mutex_lock(&cma->lock);
	for (;;) {
		start = find_next_zero_bit(cma->bitmap, bitmap_maxno, end);
		if (start >= bitmap_maxno)
			break;
		end = find_next_bit(cma->bitmap, bitmap_maxno, start);
		maxchunk = max(end - start, maxchunk);
	}
	mutex_unlock(&cma->lock);
	*val = (u64)maxchunk << cma->order_per_bit;

	return 0;
}