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
struct usb_config_descriptor {int bMaxPower; int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  bConfigurationValue; int /*<<< orphan*/  bNumInterfaces; } ;

/* Variables and functions */
 int USB_SPEED_SUPER ; 
 char* format_config ; 
 int /*<<< orphan*/  sprintf (char*,char*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *usb_dump_config_descriptor(char *start, char *end,
				const struct usb_config_descriptor *desc,
				int active, int speed)
{
	int mul;

	if (start > end)
		return start;
	if (speed >= USB_SPEED_SUPER)
		mul = 8;
	else
		mul = 2;
	start += sprintf(start, format_config,
			 /* mark active/actual/current cfg. */
			 active ? '*' : ' ',
			 desc->bNumInterfaces,
			 desc->bConfigurationValue,
			 desc->bmAttributes,
			 desc->bMaxPower * mul);
	return start;
}