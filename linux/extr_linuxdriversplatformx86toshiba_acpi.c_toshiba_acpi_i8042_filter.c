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
struct serio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hotkey_work; } ;

/* Variables and functions */
 unsigned char I8042_STR_AUXDATA ; 
 unsigned char TOS1900_FN_SCAN ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 TYPE_1__* toshiba_acpi ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool toshiba_acpi_i8042_filter(unsigned char data, unsigned char str,
				      struct serio *port)
{
	if (str & I8042_STR_AUXDATA)
		return false;

	if (unlikely(data == 0xe0))
		return false;

	if ((data & 0x7f) == TOS1900_FN_SCAN) {
		schedule_work(&toshiba_acpi->hotkey_work);
		return true;
	}

	return false;
}