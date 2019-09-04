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
 int /*<<< orphan*/  LL_ERROR ; 
 int /*<<< orphan*/  LL_INFO ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TMP006_CONV_2 ; 
 int /*<<< orphan*/ * bm222_init (int) ; 
 int /*<<< orphan*/ * s_accel_ctx ; 
 int s_tmp006_addr ; 
 int /*<<< orphan*/  tmp006_init (int,int /*<<< orphan*/ ,int) ; 

void data_init_sensors(int tmp006_addr, int bm222_addr) {
  s_tmp006_addr = tmp006_addr;
  if (!tmp006_init(tmp006_addr, TMP006_CONV_2, false)) {
    LOG(LL_ERROR, ("Failed to init temperature sensor"));
  } else {
    LOG(LL_INFO, ("Temperature sensor initialized"));
  }
  s_accel_ctx = bm222_init(bm222_addr);
  if (s_accel_ctx == NULL) {
    LOG(LL_ERROR, ("Failed to init accelerometer"));
  } else {
    LOG(LL_INFO, ("Accelerometer initialized"));
  }
}