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
struct rfkill {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int rbtn_get (struct acpi_device*) ; 
 int /*<<< orphan*/  rfkill_set_states (struct rfkill*,int,int) ; 

__attribute__((used)) static void rbtn_rfkill_query(struct rfkill *rfkill, void *data)
{
	struct acpi_device *device = data;
	int state;

	state = rbtn_get(device);
	if (state < 0)
		return;

	rfkill_set_states(rfkill, state, state);
}