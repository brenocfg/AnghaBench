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

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  css_schedule_eval_all_unreg (int) ; 

void css_schedule_reprobe(void)
{
	/* Schedule with a delay to allow merging of subsequent calls. */
	css_schedule_eval_all_unreg(1 * HZ);
}