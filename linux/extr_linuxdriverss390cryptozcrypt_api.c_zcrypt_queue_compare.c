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
struct zcrypt_queue {TYPE_1__* queue; int /*<<< orphan*/  load; } ;
struct TYPE_2__ {scalar_t__ total_request_count; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool zcrypt_queue_compare(struct zcrypt_queue *zq,
					struct zcrypt_queue *pref_zq,
					unsigned int weight,
					unsigned int pref_weight)
{
	if (!pref_zq)
		return false;
	weight += atomic_read(&zq->load);
	pref_weight += atomic_read(&pref_zq->load);
	if (weight == pref_weight)
		return zq->queue->total_request_count >
			pref_zq->queue->total_request_count;
	return weight > pref_weight;
}