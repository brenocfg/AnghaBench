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
 int /*<<< orphan*/  ASYNC_get_current_job () ; 
 int /*<<< orphan*/  ASYNC_pause_job () ; 
 int /*<<< orphan*/  currjob ; 

__attribute__((used)) static int save_current(void *args)
{
    currjob = ASYNC_get_current_job();
    ASYNC_pause_job();

    return 1;
}