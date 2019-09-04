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
struct rfkill_ops {int dummy; } ;
struct asus_rfkill {int control_id; int /*<<< orphan*/ * rfkill; struct asus_laptop* asus; } ;
struct asus_laptop {TYPE_1__* platform_device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * rfkill_alloc (char const*,int /*<<< orphan*/ *,int,struct rfkill_ops const*,struct asus_rfkill*) ; 
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ *) ; 
 int rfkill_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asus_rfkill_setup(struct asus_laptop *asus, struct asus_rfkill *rfk,
			     const char *name, int control_id, int type,
			     const struct rfkill_ops *ops)
{
	int result;

	rfk->control_id = control_id;
	rfk->asus = asus;
	rfk->rfkill = rfkill_alloc(name, &asus->platform_device->dev,
				   type, ops, rfk);
	if (!rfk->rfkill)
		return -EINVAL;

	result = rfkill_register(rfk->rfkill);
	if (result) {
		rfkill_destroy(rfk->rfkill);
		rfk->rfkill = NULL;
	}

	return result;
}