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
struct TYPE_3__ {int fdstate; int /*<<< orphan*/  fd; int /*<<< orphan*/  fileName; } ;
typedef  TYPE_1__ Vfd ;
typedef  size_t File ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DO_DB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Delete (size_t) ; 
 int FD_TEMP_FILE_LIMIT ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  VFD_CLOSED ; 
 TYPE_1__* VfdCache ; 
 scalar_t__ close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_sync_elevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  nfile ; 

__attribute__((used)) static void
LruDelete(File file)
{
	Vfd		   *vfdP;

	Assert(file != 0);

	DO_DB(elog(LOG, "LruDelete %d (%s)",
			   file, VfdCache[file].fileName));

	vfdP = &VfdCache[file];

	/*
	 * Close the file.  We aren't expecting this to fail; if it does, better
	 * to leak the FD than to mess up our internal state.
	 */
	if (close(vfdP->fd) != 0)
		elog(vfdP->fdstate & FD_TEMP_FILE_LIMIT ? LOG : data_sync_elevel(LOG),
			 "could not close file \"%s\": %m", vfdP->fileName);
	vfdP->fd = VFD_CLOSED;
	--nfile;

	/* delete the vfd record from the LRU ring */
	Delete(file);
}