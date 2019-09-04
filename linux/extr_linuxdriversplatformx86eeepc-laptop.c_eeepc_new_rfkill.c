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
struct rfkill {int dummy; } ;
struct eeepc_laptop {TYPE_1__* platform_device; } ;
typedef  enum rfkill_type { ____Placeholder_rfkill_type } rfkill_type ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int acpi_setter_handle (struct eeepc_laptop*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeepc_rfkill_ops ; 
 int get_acpi (struct eeepc_laptop*,int) ; 
 struct rfkill* rfkill_alloc (char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_destroy (struct rfkill*) ; 
 int /*<<< orphan*/  rfkill_init_sw_state (struct rfkill*,int) ; 
 int rfkill_register (struct rfkill*) ; 

__attribute__((used)) static int eeepc_new_rfkill(struct eeepc_laptop *eeepc,
			    struct rfkill **rfkill,
			    const char *name,
			    enum rfkill_type type, int cm)
{
	acpi_handle handle;
	int result;

	result = acpi_setter_handle(eeepc, cm, &handle);
	if (result < 0)
		return result;

	*rfkill = rfkill_alloc(name, &eeepc->platform_device->dev, type,
			       &eeepc_rfkill_ops, handle);

	if (!*rfkill)
		return -EINVAL;

	rfkill_init_sw_state(*rfkill, get_acpi(eeepc, cm) != 1);
	result = rfkill_register(*rfkill);
	if (result) {
		rfkill_destroy(*rfkill);
		*rfkill = NULL;
		return result;
	}
	return 0;
}