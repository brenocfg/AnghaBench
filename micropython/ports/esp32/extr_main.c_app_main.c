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
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_NVS_NEW_VERSION_FOUND ; 
 scalar_t__ ESP_ERR_NVS_NO_FREE_PAGES ; 
 int /*<<< orphan*/  MP_TASK_COREID ; 
 int /*<<< orphan*/  MP_TASK_PRIORITY ; 
 int /*<<< orphan*/  MP_TASK_STACK_LEN ; 
 int /*<<< orphan*/  mp_main_task_handle ; 
 int /*<<< orphan*/  mp_task ; 
 int /*<<< orphan*/  nvs_flash_erase () ; 
 scalar_t__ nvs_flash_init () ; 
 int /*<<< orphan*/  xTaskCreatePinnedToCore (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void app_main(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }
    xTaskCreatePinnedToCore(mp_task, "mp_task", MP_TASK_STACK_LEN, NULL, MP_TASK_PRIORITY, &mp_main_task_handle, MP_TASK_COREID);
}