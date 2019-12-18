#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int entrysize; int /*<<< orphan*/  keysize; } ;
typedef  int /*<<< orphan*/  PortalHashEnt ;
typedef  TYPE_1__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/ * AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_ELEM ; 
 int /*<<< orphan*/  MAX_PORTALNAME_LEN ; 
 int /*<<< orphan*/  PORTALS_PER_USER ; 
 int /*<<< orphan*/  PortalHashTable ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/ * TopPortalContext ; 
 int /*<<< orphan*/  hash_create (char*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

void
EnablePortalManager(void)
{
	HASHCTL		ctl;

	Assert(TopPortalContext == NULL);

	TopPortalContext = AllocSetContextCreate(TopMemoryContext,
											 "TopPortalContext",
											 ALLOCSET_DEFAULT_SIZES);

	ctl.keysize = MAX_PORTALNAME_LEN;
	ctl.entrysize = sizeof(PortalHashEnt);

	/*
	 * use PORTALS_PER_USER as a guess of how many hash table entries to
	 * create, initially
	 */
	PortalHashTable = hash_create("Portal hash", PORTALS_PER_USER,
								  &ctl, HASH_ELEM);
}