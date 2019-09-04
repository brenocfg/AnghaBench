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
struct sdebug_queue {int /*<<< orphan*/  in_use_bm; } ;
struct device_driver {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int SDEBUG_CANQUEUE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  block_unblock_all_queues (int) ; 
 int find_last_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  retired_max_queue ; 
 int sdebug_max_queue ; 
 struct sdebug_queue* sdebug_q_arr ; 
 int sscanf (char const*,char*,int*) ; 
 int submit_queues ; 

__attribute__((used)) static ssize_t max_queue_store(struct device_driver *ddp, const char *buf,
			       size_t count)
{
	int j, n, k, a;
	struct sdebug_queue *sqp;

	if ((count > 0) && (1 == sscanf(buf, "%d", &n)) && (n > 0) &&
	    (n <= SDEBUG_CANQUEUE)) {
		block_unblock_all_queues(true);
		k = 0;
		for (j = 0, sqp = sdebug_q_arr; j < submit_queues;
		     ++j, ++sqp) {
			a = find_last_bit(sqp->in_use_bm, SDEBUG_CANQUEUE);
			if (a > k)
				k = a;
		}
		sdebug_max_queue = n;
		if (k == SDEBUG_CANQUEUE)
			atomic_set(&retired_max_queue, 0);
		else if (k >= n)
			atomic_set(&retired_max_queue, k + 1);
		else
			atomic_set(&retired_max_queue, 0);
		block_unblock_all_queues(false);
		return count;
	}
	return -EINVAL;
}