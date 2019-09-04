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
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ce_arr ; 
 int /*<<< orphan*/  cec_mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_timer ; 
 int /*<<< orphan*/  do_spring_cleaning (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_interval ; 

__attribute__((used)) static void cec_timer_fn(struct timer_list *unused)
{
	do_spring_cleaning(&ce_arr);

	cec_mod_timer(&cec_timer, timer_interval);
}