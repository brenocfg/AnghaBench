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
struct multi_stop_data {scalar_t__ state; int /*<<< orphan*/  thread_ack; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_state (struct multi_stop_data*,scalar_t__) ; 

__attribute__((used)) static void ack_state(struct multi_stop_data *msdata)
{
	if (atomic_dec_and_test(&msdata->thread_ack))
		set_state(msdata, msdata->state + 1);
}