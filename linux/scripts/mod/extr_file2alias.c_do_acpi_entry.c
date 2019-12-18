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
 int /*<<< orphan*/  DEF_FIELD_ADDR (void*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  acpi_device_id ; 
 int* cls ; 
 int* cls_msk ; 
 char** id ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int do_acpi_entry(const char *filename,
			void *symval, char *alias)
{
	DEF_FIELD_ADDR(symval, acpi_device_id, id);
	DEF_FIELD_ADDR(symval, acpi_device_id, cls);
	DEF_FIELD_ADDR(symval, acpi_device_id, cls_msk);

	if (id && strlen((const char *)*id))
		sprintf(alias, "acpi*:%s:*", *id);
	else if (cls) {
		int i, byte_shift, cnt = 0;
		unsigned int msk;

		sprintf(&alias[cnt], "acpi*:");
		cnt = 6;
		for (i = 1; i <= 3; i++) {
			byte_shift = 8 * (3-i);
			msk = (*cls_msk >> byte_shift) & 0xFF;
			if (msk)
				sprintf(&alias[cnt], "%02x",
					(*cls >> byte_shift) & 0xFF);
			else
				sprintf(&alias[cnt], "??");
			cnt += 2;
		}
		sprintf(&alias[cnt], ":*");
	}
	return 1;
}