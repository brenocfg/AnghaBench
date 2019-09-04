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
 int /*<<< orphan*/  mips_cdmm_device_id ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int type ; 

__attribute__((used)) static int do_mips_cdmm_entry(const char *filename,
			      void *symval, char *alias)
{
	DEF_FIELD(symval, mips_cdmm_device_id, type);

	sprintf(alias, "mipscdmm:t%02X*", type);
	return 1;
}