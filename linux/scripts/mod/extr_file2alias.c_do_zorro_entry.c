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
 scalar_t__ ZORRO_WILDCARD ; 
 scalar_t__ id ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  zorro_device_id ; 

__attribute__((used)) static int do_zorro_entry(const char *filename, void *symval,
			  char *alias)
{
	DEF_FIELD(symval, zorro_device_id, id);
	strcpy(alias, "zorro:");
	ADD(alias, "i", id != ZORRO_WILDCARD, id);
	return 1;
}