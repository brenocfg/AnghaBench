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
typedef  int /*<<< orphan*/  CameraState ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG (char*,int) ; 
 int /*<<< orphan*/  MSM_CAMERA_I2C_BYTE_DATA ; 
 int sensor_write_regs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_exposure (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  start_reg_array ; 

__attribute__((used)) static void front_start(CameraState *s) {
  int err;

  set_exposure(s, 1.0, 1.0);

  err = sensor_write_regs(s, start_reg_array, ARRAYSIZE(start_reg_array), MSM_CAMERA_I2C_BYTE_DATA);
  LOG("sensor start regs: %d", err);
}