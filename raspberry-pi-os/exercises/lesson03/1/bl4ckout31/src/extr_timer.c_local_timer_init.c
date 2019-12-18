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
 int /*<<< orphan*/  LTIMER_CTRL ; 
 int LTIMER_CTRL_VALUE ; 
 int interval ; 
 int /*<<< orphan*/  put32 (int /*<<< orphan*/ ,int) ; 

void local_timer_init ( void )
{
	put32(LTIMER_CTRL, (interval | LTIMER_CTRL_VALUE));
}