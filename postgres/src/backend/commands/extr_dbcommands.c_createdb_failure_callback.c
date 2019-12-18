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
struct TYPE_2__ {int /*<<< orphan*/  dest_dboid; int /*<<< orphan*/  src_dboid; } ;
typedef  TYPE_1__ createdb_failure_params ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatabaseRelationId ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShareLock ; 
 int /*<<< orphan*/  UnlockSharedObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_dbtablespaces (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
createdb_failure_callback(int code, Datum arg)
{
	createdb_failure_params *fparms = (createdb_failure_params *) DatumGetPointer(arg);

	/*
	 * Release lock on source database before doing recursive remove. This is
	 * not essential but it seems desirable to release the lock as soon as
	 * possible.
	 */
	UnlockSharedObject(DatabaseRelationId, fparms->src_dboid, 0, ShareLock);

	/* Throw away any successfully copied subdirectories */
	remove_dbtablespaces(fparms->dest_dboid);
}