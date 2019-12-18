#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fdstate; int /*<<< orphan*/  resowner; } ;
typedef  size_t File ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  FD_CLOSE_AT_EOXACT ; 
 int /*<<< orphan*/  ResourceOwnerRememberFile (int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* VfdCache ; 
 int have_xact_temporary_files ; 

__attribute__((used)) static void
RegisterTemporaryFile(File file)
{
	ResourceOwnerRememberFile(CurrentResourceOwner, file);
	VfdCache[file].resowner = CurrentResourceOwner;

	/* Backup mechanism for closing at end of xact. */
	VfdCache[file].fdstate |= FD_CLOSE_AT_EOXACT;
	have_xact_temporary_files = true;
}