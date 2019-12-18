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
struct TYPE_2__ {int /*<<< orphan*/  dest_tsoid; int /*<<< orphan*/  dest_dboid; } ;
typedef  TYPE_1__ movedb_failure_params ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 char* GetDatabasePath (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmtree (char*,int) ; 

__attribute__((used)) static void
movedb_failure_callback(int code, Datum arg)
{
	movedb_failure_params *fparms = (movedb_failure_params *) DatumGetPointer(arg);
	char	   *dstpath;

	/* Get rid of anything we managed to copy to the target directory */
	dstpath = GetDatabasePath(fparms->dest_dboid, fparms->dest_tsoid);

	(void) rmtree(dstpath, true);
}