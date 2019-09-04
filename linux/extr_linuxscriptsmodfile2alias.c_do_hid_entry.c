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

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  DEF_FIELD (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ HID_ANY_ID ; 
 scalar_t__ HID_BUS_ANY ; 
 scalar_t__ HID_GROUP_ANY ; 
 scalar_t__ bus ; 
 scalar_t__ group ; 
 int /*<<< orphan*/  hid_device_id ; 
 scalar_t__ product ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 scalar_t__ vendor ; 

__attribute__((used)) static int do_hid_entry(const char *filename,
			     void *symval, char *alias)
{
	DEF_FIELD(symval, hid_device_id, bus);
	DEF_FIELD(symval, hid_device_id, group);
	DEF_FIELD(symval, hid_device_id, vendor);
	DEF_FIELD(symval, hid_device_id, product);

	sprintf(alias, "hid:");
	ADD(alias, "b", bus != HID_BUS_ANY, bus);
	ADD(alias, "g", group != HID_GROUP_ANY, group);
	ADD(alias, "v", vendor != HID_ANY_ID, vendor);
	ADD(alias, "p", product != HID_ANY_ID, product);

	return 1;
}