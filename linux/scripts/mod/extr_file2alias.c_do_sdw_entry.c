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
 int /*<<< orphan*/  add_wildcard (char*) ; 
 scalar_t__ mfg_id ; 
 scalar_t__ part_id ; 
 int /*<<< orphan*/  sdw_device_id ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int do_sdw_entry(const char *filename, void *symval, char *alias)
{
	DEF_FIELD(symval, sdw_device_id, mfg_id);
	DEF_FIELD(symval, sdw_device_id, part_id);

	strcpy(alias, "sdw:");
	ADD(alias, "m", mfg_id != 0, mfg_id);
	ADD(alias, "p", part_id != 0, part_id);

	add_wildcard(alias);
	return 1;
}