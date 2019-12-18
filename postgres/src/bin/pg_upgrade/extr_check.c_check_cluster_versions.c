#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ major_version; scalar_t__ bin_version; } ;
struct TYPE_3__ {scalar_t__ major_version; scalar_t__ bin_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int GET_MAJOR_VERSION (scalar_t__) ; 
 int /*<<< orphan*/  PG_MAJORVERSION ; 
 scalar_t__ PG_VERSION_NUM ; 
 int /*<<< orphan*/  check_ok () ; 
 TYPE_2__ new_cluster ; 
 TYPE_1__ old_cluster ; 
 int /*<<< orphan*/  pg_fatal (char*,...) ; 
 int /*<<< orphan*/  prep_status (char*) ; 

void
check_cluster_versions(void)
{
	prep_status("Checking cluster versions");

	/* cluster versions should already have been obtained */
	Assert(old_cluster.major_version != 0);
	Assert(new_cluster.major_version != 0);

	/*
	 * We allow upgrades from/to the same major version for alpha/beta
	 * upgrades
	 */

	if (GET_MAJOR_VERSION(old_cluster.major_version) < 804)
		pg_fatal("This utility can only upgrade from PostgreSQL version 8.4 and later.\n");

	/* Only current PG version is supported as a target */
	if (GET_MAJOR_VERSION(new_cluster.major_version) != GET_MAJOR_VERSION(PG_VERSION_NUM))
		pg_fatal("This utility can only upgrade to PostgreSQL version %s.\n",
				 PG_MAJORVERSION);

	/*
	 * We can't allow downgrading because we use the target pg_dump, and
	 * pg_dump cannot operate on newer database versions, only current and
	 * older versions.
	 */
	if (old_cluster.major_version > new_cluster.major_version)
		pg_fatal("This utility cannot be used to downgrade to older major PostgreSQL versions.\n");

	/* Ensure binaries match the designated data directories */
	if (GET_MAJOR_VERSION(old_cluster.major_version) !=
		GET_MAJOR_VERSION(old_cluster.bin_version))
		pg_fatal("Old cluster data and binary directories are from different major versions.\n");
	if (GET_MAJOR_VERSION(new_cluster.major_version) !=
		GET_MAJOR_VERSION(new_cluster.bin_version))
		pg_fatal("New cluster data and binary directories are from different major versions.\n");

	check_ok();
}