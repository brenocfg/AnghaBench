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
struct msg_sender {size_t msgsz; int /*<<< orphan*/  list; int /*<<< orphan*/  tsk; } ;
struct msg_queue {int /*<<< orphan*/  q_senders; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ss_add(struct msg_queue *msq,
			  struct msg_sender *mss, size_t msgsz)
{
	mss->tsk = current;
	mss->msgsz = msgsz;
	__set_current_state(TASK_INTERRUPTIBLE);
	list_add_tail(&mss->list, &msq->q_senders);
}