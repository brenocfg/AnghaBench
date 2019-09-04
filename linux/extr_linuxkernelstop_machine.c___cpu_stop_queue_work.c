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
struct wake_q_head {int dummy; } ;
struct cpu_stopper {int /*<<< orphan*/  thread; int /*<<< orphan*/  works; } ;
struct cpu_stop_work {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_q_add (struct wake_q_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cpu_stop_queue_work(struct cpu_stopper *stopper,
					struct cpu_stop_work *work,
					struct wake_q_head *wakeq)
{
	list_add_tail(&work->list, &stopper->works);
	wake_q_add(wakeq, stopper->thread);
}