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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * AuxProcessResourceOwner ; 
 int /*<<< orphan*/ * CurrentResourceOwner ; 
 int /*<<< orphan*/  ReleaseAuxProcessResourcesCallback ; 
 int /*<<< orphan*/ * ResourceOwnerCreate (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  on_shmem_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
CreateAuxProcessResourceOwner(void)
{
	Assert(AuxProcessResourceOwner == NULL);
	Assert(CurrentResourceOwner == NULL);
	AuxProcessResourceOwner = ResourceOwnerCreate(NULL, "AuxiliaryProcess");
	CurrentResourceOwner = AuxProcessResourceOwner;

	/*
	 * Register a shmem-exit callback for cleanup of aux-process resource
	 * owner.  (This needs to run after, e.g., ShutdownXLOG.)
	 */
	on_shmem_exit(ReleaseAuxProcessResourcesCallback, 0);

}