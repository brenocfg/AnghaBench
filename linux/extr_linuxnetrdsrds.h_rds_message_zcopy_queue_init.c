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
struct rds_msg_zcopy_queue {int /*<<< orphan*/  zcookie_head; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rds_message_zcopy_queue_init(struct rds_msg_zcopy_queue *q)
{
	spin_lock_init(&q->lock);
	INIT_LIST_HEAD(&q->zcookie_head);
}