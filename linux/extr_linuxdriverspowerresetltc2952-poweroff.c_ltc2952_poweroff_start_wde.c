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
struct ltc2952_poweroff {int /*<<< orphan*/  wde_interval; int /*<<< orphan*/  timer_wde; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ltc2952_poweroff_start_wde(struct ltc2952_poweroff *data)
{
	hrtimer_start(&data->timer_wde, data->wde_interval, HRTIMER_MODE_REL);
}