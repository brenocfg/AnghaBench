#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rbtn_data {TYPE_2__* input_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_6__ {char* name; char* phys; int /*<<< orphan*/  keybit; int /*<<< orphan*/ * evbit; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  KEY_RFKILL ; 
 TYPE_2__* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (TYPE_2__*) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rbtn_input_init(struct rbtn_data *rbtn_data)
{
	int ret;

	rbtn_data->input_dev = input_allocate_device();
	if (!rbtn_data->input_dev)
		return -ENOMEM;

	rbtn_data->input_dev->name = "DELL Wireless hotkeys";
	rbtn_data->input_dev->phys = "dellabce/input0";
	rbtn_data->input_dev->id.bustype = BUS_HOST;
	rbtn_data->input_dev->evbit[0] = BIT(EV_KEY);
	set_bit(KEY_RFKILL, rbtn_data->input_dev->keybit);

	ret = input_register_device(rbtn_data->input_dev);
	if (ret) {
		input_free_device(rbtn_data->input_dev);
		rbtn_data->input_dev = NULL;
		return ret;
	}

	return 0;
}