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
 int /*<<< orphan*/  DUPTERM_TASK_ID ; 
 int /*<<< orphan*/  MP_ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dupterm_evt_queue ; 
 int /*<<< orphan*/  dupterm_task_handler ; 
 int /*<<< orphan*/  system_os_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dupterm_task_init() {
    system_os_task(dupterm_task_handler, DUPTERM_TASK_ID, dupterm_evt_queue, MP_ARRAY_SIZE(dupterm_evt_queue));
}