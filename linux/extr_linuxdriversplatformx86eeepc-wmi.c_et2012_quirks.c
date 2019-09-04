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
struct dmi_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMI_DEV_TYPE_OEM_STRING ; 
 struct dmi_device* dmi_find_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dmi_device const*) ; 
 int /*<<< orphan*/  quirk_asus_et2012_type1 ; 
 int /*<<< orphan*/  quirk_asus_et2012_type3 ; 
 int /*<<< orphan*/ * quirks ; 
 int sscanf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void et2012_quirks(void)
{
	const struct dmi_device *dev = NULL;
	char oemstring[30];

	while ((dev = dmi_find_device(DMI_DEV_TYPE_OEM_STRING, NULL, dev))) {
		if (sscanf(dev->name, "AEMS%24c", oemstring) == 1) {
			if (oemstring[18] == '1')
				quirks = &quirk_asus_et2012_type1;
			else if (oemstring[18] == '3')
				quirks = &quirk_asus_et2012_type3;
			break;
		}
	}
}