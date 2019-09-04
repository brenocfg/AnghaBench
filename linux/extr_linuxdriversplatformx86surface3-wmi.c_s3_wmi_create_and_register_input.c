#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int product; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; char* phys; TYPE_1__ id; } ;
struct TYPE_4__ {struct input_dev* input; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_SW ; 
 int /*<<< orphan*/  SW_LID ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ s3_wmi ; 

__attribute__((used)) static int s3_wmi_create_and_register_input(struct platform_device *pdev)
{
	struct input_dev *input;
	int error;

	input = devm_input_allocate_device(&pdev->dev);
	if (!input)
		return -ENOMEM;

	input->name = "Lid Switch";
	input->phys = "button/input0";
	input->id.bustype = BUS_HOST;
	input->id.product = 0x0005;

	input_set_capability(input, EV_SW, SW_LID);

	error = input_register_device(input);
	if (error)
		goto out_err;

	s3_wmi.input = input;

	return 0;
 out_err:
	input_free_device(s3_wmi.input);
	return error;
}