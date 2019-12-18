#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {char* tablespace_suffix; } ;
struct TYPE_14__ {char* tablespace_suffix; } ;
struct TYPE_13__ {int /*<<< orphan*/  db_oid; } ;
struct TYPE_12__ {char const* old_tablespace; char* old_tablespace_suffix; char const* new_tablespace; char* new_tablespace_suffix; int /*<<< orphan*/  relname; int /*<<< orphan*/  nspname; int /*<<< orphan*/  new_relfilenode; int /*<<< orphan*/  old_relfilenode; int /*<<< orphan*/  new_db_oid; int /*<<< orphan*/  old_db_oid; } ;
struct TYPE_11__ {char const* tablespace; int /*<<< orphan*/  relname; int /*<<< orphan*/  nspname; int /*<<< orphan*/  relfilenode; } ;
typedef  TYPE_1__ RelInfo ;
typedef  TYPE_2__ FileNameMap ;
typedef  TYPE_3__ DbInfo ;

/* Variables and functions */
 TYPE_5__ new_cluster ; 
 TYPE_4__ old_cluster ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
create_rel_filename_map(const char *old_data, const char *new_data,
						const DbInfo *old_db, const DbInfo *new_db,
						const RelInfo *old_rel, const RelInfo *new_rel,
						FileNameMap *map)
{
	/* In case old/new tablespaces don't match, do them separately. */
	if (strlen(old_rel->tablespace) == 0)
	{
		/*
		 * relation belongs to the default tablespace, hence relfiles should
		 * exist in the data directories.
		 */
		map->old_tablespace = old_data;
		map->old_tablespace_suffix = "/base";
	}
	else
	{
		/* relation belongs to a tablespace, so use the tablespace location */
		map->old_tablespace = old_rel->tablespace;
		map->old_tablespace_suffix = old_cluster.tablespace_suffix;
	}

	/* Do the same for new tablespaces */
	if (strlen(new_rel->tablespace) == 0)
	{
		map->new_tablespace = new_data;
		map->new_tablespace_suffix = "/base";
	}
	else
	{
		map->new_tablespace = new_rel->tablespace;
		map->new_tablespace_suffix = new_cluster.tablespace_suffix;
	}

	map->old_db_oid = old_db->db_oid;
	map->new_db_oid = new_db->db_oid;

	/*
	 * old_relfilenode might differ from pg_class.oid (and hence
	 * new_relfilenode) because of CLUSTER, REINDEX, or VACUUM FULL.
	 */
	map->old_relfilenode = old_rel->relfilenode;

	/* new_relfilenode will match old and new pg_class.oid */
	map->new_relfilenode = new_rel->relfilenode;

	/* used only for logging and error reporting, old/new are identical */
	map->nspname = old_rel->nspname;
	map->relname = old_rel->relname;
}