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
 int /*<<< orphan*/  TAPE_DBF_AREA ; 
 int /*<<< orphan*/  ccw_driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_3590_driver ; 
 int /*<<< orphan*/  tape_3590_wq ; 

__attribute__((used)) static void
tape_3590_exit(void)
{
	ccw_driver_unregister(&tape_3590_driver);
	destroy_workqueue(tape_3590_wq);
	debug_unregister(TAPE_DBF_AREA);
}