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
struct request_queue {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int __blk_mq_sched_bio_merge (struct request_queue*,struct bio*,unsigned int) ; 
 int /*<<< orphan*/  bio_mergeable (struct bio*) ; 
 scalar_t__ blk_queue_nomerges (struct request_queue*) ; 

__attribute__((used)) static inline bool
blk_mq_sched_bio_merge(struct request_queue *q, struct bio *bio,
		unsigned int nr_segs)
{
	if (blk_queue_nomerges(q) || !bio_mergeable(bio))
		return false;

	return __blk_mq_sched_bio_merge(q, bio, nr_segs);
}