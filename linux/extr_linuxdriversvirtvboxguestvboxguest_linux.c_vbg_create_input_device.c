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
struct vbg_dev {struct input_dev* input; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; TYPE_2__ dev; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_MOUSE ; 
 int /*<<< orphan*/  BUS_PCI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  VBOX_VENDORID ; 
 int /*<<< orphan*/  VMMDEV_DEVICEID ; 
 int /*<<< orphan*/  VMMDEV_MOUSE_RANGE_MAX ; 
 int /*<<< orphan*/  VMMDEV_MOUSE_RANGE_MIN ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ ) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct vbg_dev*) ; 
 int /*<<< orphan*/  vbg_input_close ; 
 int /*<<< orphan*/  vbg_input_open ; 

__attribute__((used)) static int vbg_create_input_device(struct vbg_dev *gdev)
{
	struct input_dev *input;

	input = devm_input_allocate_device(gdev->dev);
	if (!input)
		return -ENOMEM;

	input->id.bustype = BUS_PCI;
	input->id.vendor = VBOX_VENDORID;
	input->id.product = VMMDEV_DEVICEID;
	input->open = vbg_input_open;
	input->close = vbg_input_close;
	input->dev.parent = gdev->dev;
	input->name = "VirtualBox mouse integration";

	input_set_abs_params(input, ABS_X, VMMDEV_MOUSE_RANGE_MIN,
			     VMMDEV_MOUSE_RANGE_MAX, 0, 0);
	input_set_abs_params(input, ABS_Y, VMMDEV_MOUSE_RANGE_MIN,
			     VMMDEV_MOUSE_RANGE_MAX, 0, 0);
	input_set_capability(input, EV_KEY, BTN_MOUSE);
	input_set_drvdata(input, gdev);

	gdev->input = input;

	return input_register_device(gdev->input);
}