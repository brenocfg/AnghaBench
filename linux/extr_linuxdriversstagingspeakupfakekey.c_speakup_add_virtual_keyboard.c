#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_9__ {char* name; char* phys; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; TYPE_2__ dev; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_VIRTUAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  KEY_DOWN ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (TYPE_3__*) ; 
 int input_register_device (TYPE_3__*) ; 
 TYPE_3__* virt_keyboard ; 

int speakup_add_virtual_keyboard(void)
{
	int err;

	virt_keyboard = input_allocate_device();

	if (!virt_keyboard)
		return -ENOMEM;

	virt_keyboard->name = "Speakup";
	virt_keyboard->id.bustype = BUS_VIRTUAL;
	virt_keyboard->phys = "speakup/input0";
	virt_keyboard->dev.parent = NULL;

	__set_bit(EV_KEY, virt_keyboard->evbit);
	__set_bit(KEY_DOWN, virt_keyboard->keybit);

	err = input_register_device(virt_keyboard);
	if (err) {
		input_free_device(virt_keyboard);
		virt_keyboard = NULL;
	}

	return err;
}