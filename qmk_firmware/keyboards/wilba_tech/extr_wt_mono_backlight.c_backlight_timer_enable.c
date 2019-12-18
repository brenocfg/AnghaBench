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
 int /*<<< orphan*/  OCIE3A ; 
 int /*<<< orphan*/  TIMSK3 ; 
 int /*<<< orphan*/  _BV (int /*<<< orphan*/ ) ; 

void backlight_timer_enable(void)
{
	TIMSK3 |= _BV(OCIE3A);
}