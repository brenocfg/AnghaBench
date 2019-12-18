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
typedef  int /*<<< orphan*/  u32_t ;
typedef  int /*<<< orphan*/  spiffs_check_type ;
typedef  int /*<<< orphan*/  spiffs_check_report ;

/* Variables and functions */

void myspiffs_check_callback(spiffs_check_type type, spiffs_check_report report, u32_t arg1, u32_t arg2){
  // if(SPIFFS_CHECK_PROGRESS == report) return;
  // NODE_ERR("type: %d, report: %d, arg1: %d, arg2: %d\n", type, report, arg1, arg2);
}