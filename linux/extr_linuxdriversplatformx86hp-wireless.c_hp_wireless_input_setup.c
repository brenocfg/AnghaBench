#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_7__ {char* name; char* phys; int /*<<< orphan*/  keybit; int /*<<< orphan*/ * evbit; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  KEY_RFKILL ; 
 TYPE_2__* hpwl_input_dev ; 
 TYPE_2__* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (TYPE_2__*) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hp_wireless_input_setup(void)
{
	int err;

	hpwl_input_dev = input_allocate_device();
	if (!hpwl_input_dev)
		return -ENOMEM;

	hpwl_input_dev->name = "HP Wireless hotkeys";
	hpwl_input_dev->phys = "hpq6001/input0";
	hpwl_input_dev->id.bustype = BUS_HOST;
	hpwl_input_dev->evbit[0] = BIT(EV_KEY);
	set_bit(KEY_RFKILL, hpwl_input_dev->keybit);

	err = input_register_device(hpwl_input_dev);
	if (err)
		goto err_free_dev;

	return 0;

err_free_dev:
	input_free_device(hpwl_input_dev);
	return err;
}