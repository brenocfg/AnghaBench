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
struct input_dev {int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  cmpc_accel_close ; 
 int /*<<< orphan*/  cmpc_accel_open ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmpc_accel_idev_init(struct input_dev *inputdev)
{
	set_bit(EV_ABS, inputdev->evbit);
	input_set_abs_params(inputdev, ABS_X, 0, 255, 8, 0);
	input_set_abs_params(inputdev, ABS_Y, 0, 255, 8, 0);
	input_set_abs_params(inputdev, ABS_Z, 0, 255, 8, 0);
	inputdev->open = cmpc_accel_open;
	inputdev->close = cmpc_accel_close;
}