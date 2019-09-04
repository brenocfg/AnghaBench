#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct macio_dev {TYPE_1__* bus; } ;
struct i2sbus_control {int /*<<< orphan*/  macio; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct i2sbus_control* kzalloc (int,int /*<<< orphan*/ ) ; 

int i2sbus_control_init(struct macio_dev* dev, struct i2sbus_control **c)
{
	*c = kzalloc(sizeof(struct i2sbus_control), GFP_KERNEL);
	if (!*c)
		return -ENOMEM;

	INIT_LIST_HEAD(&(*c)->list);

	(*c)->macio = dev->bus->chip;
	return 0;
}