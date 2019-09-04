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
 int /*<<< orphan*/  MP_TASK_PRIORITY ; 
 int /*<<< orphan*/  MP_TASK_STACK_LEN ; 
 int /*<<< orphan*/  mp_main_task_handle ; 
 int /*<<< orphan*/  mp_task ; 
 int /*<<< orphan*/  nvs_flash_init () ; 
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void app_main(void) {
    nvs_flash_init();
    xTaskCreate(mp_task, "mp_task", MP_TASK_STACK_LEN, NULL, MP_TASK_PRIORITY, &mp_main_task_handle);
}