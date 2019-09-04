#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ field; char* prefix; } ;
struct TYPE_5__ {scalar_t__ slot; int /*<<< orphan*/  substr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  DEF_FIELD_ADDR (void*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dmi_ascii_filter (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* dmi_fields ; 
 int /*<<< orphan*/  dmi_system_id ; 
 TYPE_1__** matches ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int do_dmi_entry(const char *filename, void *symval,
			char *alias)
{
	int i, j;
	DEF_FIELD_ADDR(symval, dmi_system_id, matches);
	sprintf(alias, "dmi*");

	for (i = 0; i < ARRAY_SIZE(dmi_fields); i++) {
		for (j = 0; j < 4; j++) {
			if ((*matches)[j].slot &&
			    (*matches)[j].slot == dmi_fields[i].field) {
				sprintf(alias + strlen(alias), ":%s*",
					dmi_fields[i].prefix);
				dmi_ascii_filter(alias + strlen(alias),
						 (*matches)[j].substr);
				strcat(alias, "*");
			}
		}
	}

	strcat(alias, ":");
	return 1;
}