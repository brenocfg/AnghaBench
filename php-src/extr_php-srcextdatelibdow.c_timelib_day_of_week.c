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
typedef  int /*<<< orphan*/  timelib_sll ;

/* Variables and functions */
 int /*<<< orphan*/  timelib_day_of_week_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

timelib_sll timelib_day_of_week(timelib_sll y, timelib_sll m, timelib_sll d)
{
	return timelib_day_of_week_ex(y, m, d, 0);
}