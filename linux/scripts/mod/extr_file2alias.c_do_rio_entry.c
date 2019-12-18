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
 scalar_t__ RIO_ANY_ID ; 
 int /*<<< orphan*/  add_wildcard (char*) ; 
 scalar_t__ asm_did ; 
 scalar_t__ asm_vid ; 
 scalar_t__ did ; 
 int /*<<< orphan*/  rio_device_id ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ vid ; 

__attribute__((used)) static int do_rio_entry(const char *filename,
			void *symval, char *alias)
{
	DEF_FIELD(symval, rio_device_id, did);
	DEF_FIELD(symval, rio_device_id, vid);
	DEF_FIELD(symval, rio_device_id, asm_did);
	DEF_FIELD(symval, rio_device_id, asm_vid);

	strcpy(alias, "rapidio:");
	ADD(alias, "v", vid != RIO_ANY_ID, vid);
	ADD(alias, "d", did != RIO_ANY_ID, did);
	ADD(alias, "av", asm_vid != RIO_ANY_ID, asm_vid);
	ADD(alias, "ad", asm_did != RIO_ANY_ID, asm_did);

	add_wildcard(alias);
	return 1;
}