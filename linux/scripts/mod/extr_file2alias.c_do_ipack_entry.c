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
 scalar_t__ IPACK_ANY_FORMAT ; 
 scalar_t__ IPACK_ANY_ID ; 
 int /*<<< orphan*/  add_wildcard (char*) ; 
 scalar_t__ device ; 
 scalar_t__ format ; 
 int /*<<< orphan*/  ipack_device_id ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ vendor ; 

__attribute__((used)) static int do_ipack_entry(const char *filename,
			  void *symval, char *alias)
{
	DEF_FIELD(symval, ipack_device_id, format);
	DEF_FIELD(symval, ipack_device_id, vendor);
	DEF_FIELD(symval, ipack_device_id, device);
	strcpy(alias, "ipack:");
	ADD(alias, "f", format != IPACK_ANY_FORMAT, format);
	ADD(alias, "v", vendor != IPACK_ANY_ID, vendor);
	ADD(alias, "d", device != IPACK_ANY_ID, device);
	add_wildcard(alias);
	return 1;
}