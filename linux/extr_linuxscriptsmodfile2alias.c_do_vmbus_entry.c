#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * b; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_FIELD_ADDR (void*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int TO_NATIVE (int /*<<< orphan*/ ) ; 
 TYPE_1__* guid ; 
 int /*<<< orphan*/  hv_vmbus_device_id ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int do_vmbus_entry(const char *filename, void *symval,
			  char *alias)
{
	int i;
	DEF_FIELD_ADDR(symval, hv_vmbus_device_id, guid);
	char guid_name[(sizeof(*guid) + 1) * 2];

	for (i = 0; i < (sizeof(*guid) * 2); i += 2)
		sprintf(&guid_name[i], "%02x", TO_NATIVE((guid->b)[i/2]));

	strcpy(alias, "vmbus:");
	strcat(alias, guid_name);

	return 1;
}