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
 int /*<<< orphan*/  DEF_FIELD_ADDR (void*,int /*<<< orphan*/ ,char**) ; 
 char* MEI_CL_MODULE_PREFIX ; 
 scalar_t__ MEI_CL_VERSION_ANY ; 
 int /*<<< orphan*/  add_uuid (char*,char*) ; 
 int /*<<< orphan*/  mei_cl_device_id ; 
 char** name ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 char** uuid ; 
 scalar_t__ version ; 

__attribute__((used)) static int do_mei_entry(const char *filename, void *symval,
			char *alias)
{
	DEF_FIELD_ADDR(symval, mei_cl_device_id, name);
	DEF_FIELD_ADDR(symval, mei_cl_device_id, uuid);
	DEF_FIELD(symval, mei_cl_device_id, version);

	sprintf(alias, MEI_CL_MODULE_PREFIX);
	sprintf(alias + strlen(alias), "%s:",  (*name)[0]  ? *name : "*");
	add_uuid(alias, *uuid);
	ADD(alias, ":", version != MEI_CL_VERSION_ANY, version);

	strcat(alias, ":*");

	return 1;
}