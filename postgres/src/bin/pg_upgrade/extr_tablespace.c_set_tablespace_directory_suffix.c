#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cat_ver; } ;
struct TYPE_5__ {TYPE_1__ controldata; int /*<<< orphan*/  major_version_str; int /*<<< orphan*/  tablespace_suffix; int /*<<< orphan*/  major_version; } ;
typedef  TYPE_2__ ClusterInfo ;

/* Variables and functions */
 int GET_MAJOR_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_strdup (char*) ; 
 int /*<<< orphan*/  psprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_tablespace_directory_suffix(ClusterInfo *cluster)
{
	if (GET_MAJOR_VERSION(cluster->major_version) <= 804)
		cluster->tablespace_suffix = pg_strdup("");
	else
	{
		/* This cluster has a version-specific subdirectory */

		/* The leading slash is needed to start a new directory. */
		cluster->tablespace_suffix = psprintf("/PG_%s_%d",
											  cluster->major_version_str,
											  cluster->controldata.cat_ver);
	}
}