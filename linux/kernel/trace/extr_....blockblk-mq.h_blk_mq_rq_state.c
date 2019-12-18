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
struct request {int /*<<< orphan*/  state; } ;
typedef  enum mq_rq_state { ____Placeholder_mq_rq_state } mq_rq_state ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline enum mq_rq_state blk_mq_rq_state(struct request *rq)
{
	return READ_ONCE(rq->state);
}