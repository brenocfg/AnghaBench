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
 int /*<<< orphan*/  io_schedule_finish (int) ; 
 int io_schedule_prepare () ; 
 int /*<<< orphan*/  schedule () ; 

void io_schedule(void)
{
	int token;

	token = io_schedule_prepare();
	schedule();
	io_schedule_finish(token);
}