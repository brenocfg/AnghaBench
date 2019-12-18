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
 int /*<<< orphan*/  DEF_FIELD_ADDR (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* RPMSG_DEVICE_MODALIAS_FMT ; 
 int /*<<< orphan*/ * name ; 
 int /*<<< orphan*/  rpmsg_device_id ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_rpmsg_entry(const char *filename, void *symval,
			  char *alias)
{
	DEF_FIELD_ADDR(symval, rpmsg_device_id, name);
	sprintf(alias, RPMSG_DEVICE_MODALIAS_FMT, *name);

	return 1;
}