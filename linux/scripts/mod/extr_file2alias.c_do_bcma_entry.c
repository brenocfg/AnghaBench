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
 scalar_t__ BCMA_ANY_CLASS ; 
 scalar_t__ BCMA_ANY_ID ; 
 scalar_t__ BCMA_ANY_MANUF ; 
 scalar_t__ BCMA_ANY_REV ; 
 int /*<<< orphan*/  DEF_FIELD (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  add_wildcard (char*) ; 
 int /*<<< orphan*/  bcma_device_id ; 
 scalar_t__ class ; 
 scalar_t__ id ; 
 scalar_t__ manuf ; 
 scalar_t__ rev ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int do_bcma_entry(const char *filename,
			 void *symval, char *alias)
{
	DEF_FIELD(symval, bcma_device_id, manuf);
	DEF_FIELD(symval, bcma_device_id, id);
	DEF_FIELD(symval, bcma_device_id, rev);
	DEF_FIELD(symval, bcma_device_id, class);

	strcpy(alias, "bcma:");
	ADD(alias, "m", manuf != BCMA_ANY_MANUF, manuf);
	ADD(alias, "id", id != BCMA_ANY_ID, id);
	ADD(alias, "rev", rev != BCMA_ANY_REV, rev);
	ADD(alias, "cl", class != BCMA_ANY_CLASS, class);
	add_wildcard(alias);
	return 1;
}