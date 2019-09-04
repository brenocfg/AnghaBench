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
typedef  unsigned long u8 ;
struct rfkill {int dummy; } ;
typedef  enum rfkill_type { ____Placeholder_rfkill_type } rfkill_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct rfkill* ERR_PTR (int) ; 
 int /*<<< orphan*/  OT_EC_DEVICE_STATE_ADDRESS ; 
 int /*<<< orphan*/  ec_read (int /*<<< orphan*/ ,unsigned long*) ; 
 TYPE_1__* oaktrail_device ; 
 int /*<<< orphan*/  oaktrail_rfkill_ops ; 
 struct rfkill* rfkill_alloc (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  rfkill_destroy (struct rfkill*) ; 
 int /*<<< orphan*/  rfkill_init_sw_state (struct rfkill*,int) ; 
 int rfkill_register (struct rfkill*) ; 

__attribute__((used)) static struct rfkill *oaktrail_rfkill_new(char *name, enum rfkill_type type,
					  unsigned long mask)
{
	struct rfkill *rfkill_dev;
	u8 value;
	int err;

	rfkill_dev = rfkill_alloc(name, &oaktrail_device->dev, type,
				  &oaktrail_rfkill_ops, (void *)mask);
	if (!rfkill_dev)
		return ERR_PTR(-ENOMEM);

	ec_read(OT_EC_DEVICE_STATE_ADDRESS, &value);
	rfkill_init_sw_state(rfkill_dev, (value & mask) != 1);

	err = rfkill_register(rfkill_dev);
	if (err) {
		rfkill_destroy(rfkill_dev);
		return ERR_PTR(err);
	}

	return rfkill_dev;
}