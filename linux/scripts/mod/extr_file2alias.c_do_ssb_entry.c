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
 scalar_t__ SSB_ANY_ID ; 
 scalar_t__ SSB_ANY_REV ; 
 scalar_t__ SSB_ANY_VENDOR ; 
 int /*<<< orphan*/  add_wildcard (char*) ; 
 scalar_t__ coreid ; 
 scalar_t__ revision ; 
 int /*<<< orphan*/  ssb_device_id ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ vendor ; 

__attribute__((used)) static int do_ssb_entry(const char *filename,
			void *symval, char *alias)
{
	DEF_FIELD(symval, ssb_device_id, vendor);
	DEF_FIELD(symval, ssb_device_id, coreid);
	DEF_FIELD(symval, ssb_device_id, revision);

	strcpy(alias, "ssb:");
	ADD(alias, "v", vendor != SSB_ANY_VENDOR, vendor);
	ADD(alias, "id", coreid != SSB_ANY_ID, coreid);
	ADD(alias, "rev", revision != SSB_ANY_REV, revision);
	add_wildcard(alias);
	return 1;
}