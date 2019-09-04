#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
struct virtqueue {int dummy; } ;
struct airq_info {int /*<<< orphan*/  lock; TYPE_1__* aiv; } ;
struct TYPE_3__ {scalar_t__ vector; } ;

/* Variables and functions */
 int MAX_AIRQ_AREAS ; 
 struct airq_info** airq_areas ; 
 unsigned long airq_iv_alloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  airq_iv_set_ptr (TYPE_1__*,unsigned long,unsigned long) ; 
 struct airq_info* new_airq_info () ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned long get_airq_indicator(struct virtqueue *vqs[], int nvqs,
					u64 *first, void **airq_info)
{
	int i, j;
	struct airq_info *info;
	unsigned long indicator_addr = 0;
	unsigned long bit, flags;

	for (i = 0; i < MAX_AIRQ_AREAS && !indicator_addr; i++) {
		if (!airq_areas[i])
			airq_areas[i] = new_airq_info();
		info = airq_areas[i];
		if (!info)
			return 0;
		write_lock_irqsave(&info->lock, flags);
		bit = airq_iv_alloc(info->aiv, nvqs);
		if (bit == -1UL) {
			/* Not enough vacancies. */
			write_unlock_irqrestore(&info->lock, flags);
			continue;
		}
		*first = bit;
		*airq_info = info;
		indicator_addr = (unsigned long)info->aiv->vector;
		for (j = 0; j < nvqs; j++) {
			airq_iv_set_ptr(info->aiv, bit + j,
					(unsigned long)vqs[j]);
		}
		write_unlock_irqrestore(&info->lock, flags);
	}
	return indicator_addr;
}