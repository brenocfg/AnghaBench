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
 int /*<<< orphan*/  PG_VERSION_NUM ; 
 int /*<<< orphan*/  datadir_target ; 
 int /*<<< orphan*/  do_sync ; 
 scalar_t__ dry_run ; 
 int /*<<< orphan*/  fsync_pgdata (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
syncTargetDirectory(void)
{
	if (!do_sync || dry_run)
		return;

	fsync_pgdata(datadir_target, PG_VERSION_NUM);
}