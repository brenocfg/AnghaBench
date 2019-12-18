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
 scalar_t__ PA_HVERSION_ANY_ID ; 
 scalar_t__ PA_HVERSION_REV_ANY_ID ; 
 scalar_t__ PA_HWTYPE_ANY_ID ; 
 scalar_t__ PA_SVERSION_ANY_ID ; 
 int /*<<< orphan*/  add_wildcard (char*) ; 
 scalar_t__ hversion ; 
 scalar_t__ hversion_rev ; 
 scalar_t__ hw_type ; 
 int /*<<< orphan*/  parisc_device_id ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ sversion ; 

__attribute__((used)) static int do_parisc_entry(const char *filename, void *symval,
		char *alias)
{
	DEF_FIELD(symval, parisc_device_id, hw_type);
	DEF_FIELD(symval, parisc_device_id, hversion);
	DEF_FIELD(symval, parisc_device_id, hversion_rev);
	DEF_FIELD(symval, parisc_device_id, sversion);

	strcpy(alias, "parisc:");
	ADD(alias, "t", hw_type != PA_HWTYPE_ANY_ID, hw_type);
	ADD(alias, "hv", hversion != PA_HVERSION_ANY_ID, hversion);
	ADD(alias, "rev", hversion_rev != PA_HVERSION_REV_ANY_ID, hversion_rev);
	ADD(alias, "sv", sversion != PA_SVERSION_ANY_ID, sversion);

	add_wildcard(alias);
	return 1;
}