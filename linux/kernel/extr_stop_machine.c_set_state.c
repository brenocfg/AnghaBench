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
struct multi_stop_data {int /*<<< orphan*/  state; int /*<<< orphan*/  num_threads; int /*<<< orphan*/  thread_ack; } ;
typedef  enum multi_stop_state { ____Placeholder_multi_stop_state } multi_stop_state ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void set_state(struct multi_stop_data *msdata,
		      enum multi_stop_state newstate)
{
	/* Reset ack counter. */
	atomic_set(&msdata->thread_ack, msdata->num_threads);
	smp_wmb();
	WRITE_ONCE(msdata->state, newstate);
}