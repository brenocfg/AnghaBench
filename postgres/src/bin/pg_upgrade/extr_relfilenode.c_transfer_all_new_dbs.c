#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  db_name; } ;
struct TYPE_7__ {int ndbs; TYPE_2__* dbs; } ;
typedef  int /*<<< orphan*/  FileNameMap ;
typedef  TYPE_1__ DbInfoArr ;
typedef  TYPE_2__ DbInfo ;

/* Variables and functions */
 int /*<<< orphan*/ * gen_db_file_maps (TYPE_2__*,TYPE_2__*,int*,char*,char*) ; 
 int /*<<< orphan*/  pg_fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_maps (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transfer_single_new_db (int /*<<< orphan*/ *,int,char*) ; 

void
transfer_all_new_dbs(DbInfoArr *old_db_arr, DbInfoArr *new_db_arr,
					 char *old_pgdata, char *new_pgdata, char *old_tablespace)
{
	int			old_dbnum,
				new_dbnum;

	/* Scan the old cluster databases and transfer their files */
	for (old_dbnum = new_dbnum = 0;
		 old_dbnum < old_db_arr->ndbs;
		 old_dbnum++, new_dbnum++)
	{
		DbInfo	   *old_db = &old_db_arr->dbs[old_dbnum],
				   *new_db = NULL;
		FileNameMap *mappings;
		int			n_maps;

		/*
		 * Advance past any databases that exist in the new cluster but not in
		 * the old, e.g. "postgres".  (The user might have removed the
		 * 'postgres' database from the old cluster.)
		 */
		for (; new_dbnum < new_db_arr->ndbs; new_dbnum++)
		{
			new_db = &new_db_arr->dbs[new_dbnum];
			if (strcmp(old_db->db_name, new_db->db_name) == 0)
				break;
		}

		if (new_dbnum >= new_db_arr->ndbs)
			pg_fatal("old database \"%s\" not found in the new cluster\n",
					 old_db->db_name);

		mappings = gen_db_file_maps(old_db, new_db, &n_maps, old_pgdata,
									new_pgdata);
		if (n_maps)
		{
			print_maps(mappings, n_maps, new_db->db_name);

			transfer_single_new_db(mappings, n_maps, old_tablespace);
		}
		/* We allocate something even for n_maps == 0 */
		pg_free(mappings);
	}

	return;
}