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
 int /*<<< orphan*/  DEF_FIELD (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DEF_FIELD_ADDR (void*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  fsl_mc_device_id ; 
 char** obj_type ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*) ; 
 int vendor ; 

__attribute__((used)) static int do_fsl_mc_entry(const char *filename, void *symval,
			   char *alias)
{
	DEF_FIELD(symval, fsl_mc_device_id, vendor);
	DEF_FIELD_ADDR(symval, fsl_mc_device_id, obj_type);

	sprintf(alias, "fsl-mc:v%08Xd%s", vendor, *obj_type);
	return 1;
}