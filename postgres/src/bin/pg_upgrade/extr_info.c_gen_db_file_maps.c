#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  major_version; } ;
struct TYPE_13__ {int nrels; TYPE_2__* rels; } ;
struct TYPE_15__ {int /*<<< orphan*/  db_name; TYPE_1__ rel_arr; } ;
struct TYPE_14__ {char* nspname; scalar_t__ reloid; char* relname; } ;
typedef  TYPE_2__ RelInfo ;
typedef  int /*<<< orphan*/  FileNameMap ;
typedef  TYPE_3__ DbInfo ;

/* Variables and functions */
 int GET_MAJOR_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_WARNING ; 
 int /*<<< orphan*/  create_rel_filename_map (char const*,char const*,TYPE_3__*,TYPE_3__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_6__ old_cluster ; 
 int /*<<< orphan*/  pg_fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 scalar_t__ pg_malloc (int) ; 
 int /*<<< orphan*/  report_unmatched_relation (TYPE_2__*,TYPE_3__*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

FileNameMap *
gen_db_file_maps(DbInfo *old_db, DbInfo *new_db,
				 int *nmaps,
				 const char *old_pgdata, const char *new_pgdata)
{
	FileNameMap *maps;
	int			old_relnum,
				new_relnum;
	int			num_maps = 0;
	bool		all_matched = true;

	/* There will certainly not be more mappings than there are old rels */
	maps = (FileNameMap *) pg_malloc(sizeof(FileNameMap) *
									 old_db->rel_arr.nrels);

	/*
	 * Each of the RelInfo arrays should be sorted by OID.  Scan through them
	 * and match them up.  If we fail to match everything, we'll abort, but
	 * first print as much info as we can about mismatches.
	 */
	old_relnum = new_relnum = 0;
	while (old_relnum < old_db->rel_arr.nrels ||
		   new_relnum < new_db->rel_arr.nrels)
	{
		RelInfo    *old_rel = (old_relnum < old_db->rel_arr.nrels) ?
		&old_db->rel_arr.rels[old_relnum] : NULL;
		RelInfo    *new_rel = (new_relnum < new_db->rel_arr.nrels) ?
		&new_db->rel_arr.rels[new_relnum] : NULL;

		/* handle running off one array before the other */
		if (!new_rel)
		{
			/*
			 * old_rel is unmatched.  This should never happen, because we
			 * force new rels to have TOAST tables if the old one did.
			 */
			report_unmatched_relation(old_rel, old_db, false);
			all_matched = false;
			old_relnum++;
			continue;
		}
		if (!old_rel)
		{
			/*
			 * new_rel is unmatched.  This shouldn't really happen either, but
			 * if it's a TOAST table, we can ignore it and continue
			 * processing, assuming that the new server made a TOAST table
			 * that wasn't needed.
			 */
			if (strcmp(new_rel->nspname, "pg_toast") != 0)
			{
				report_unmatched_relation(new_rel, new_db, true);
				all_matched = false;
			}
			new_relnum++;
			continue;
		}

		/* check for mismatched OID */
		if (old_rel->reloid < new_rel->reloid)
		{
			/* old_rel is unmatched, see comment above */
			report_unmatched_relation(old_rel, old_db, false);
			all_matched = false;
			old_relnum++;
			continue;
		}
		else if (old_rel->reloid > new_rel->reloid)
		{
			/* new_rel is unmatched, see comment above */
			if (strcmp(new_rel->nspname, "pg_toast") != 0)
			{
				report_unmatched_relation(new_rel, new_db, true);
				all_matched = false;
			}
			new_relnum++;
			continue;
		}

		/*
		 * Verify that rels of same OID have same name.  The namespace name
		 * should always match, but the relname might not match for TOAST
		 * tables (and, therefore, their indexes).
		 *
		 * TOAST table names initially match the heap pg_class oid, but
		 * pre-9.0 they can change during certain commands such as CLUSTER, so
		 * don't insist on a match if old cluster is < 9.0.
		 */
		if (strcmp(old_rel->nspname, new_rel->nspname) != 0 ||
			(strcmp(old_rel->relname, new_rel->relname) != 0 &&
			 (GET_MAJOR_VERSION(old_cluster.major_version) >= 900 ||
			  strcmp(old_rel->nspname, "pg_toast") != 0)))
		{
			pg_log(PG_WARNING, "Relation names for OID %u in database \"%s\" do not match: "
				   "old name \"%s.%s\", new name \"%s.%s\"\n",
				   old_rel->reloid, old_db->db_name,
				   old_rel->nspname, old_rel->relname,
				   new_rel->nspname, new_rel->relname);
			all_matched = false;
			old_relnum++;
			new_relnum++;
			continue;
		}

		/* OK, create a mapping entry */
		create_rel_filename_map(old_pgdata, new_pgdata, old_db, new_db,
								old_rel, new_rel, maps + num_maps);
		num_maps++;
		old_relnum++;
		new_relnum++;
	}

	if (!all_matched)
		pg_fatal("Failed to match up old and new tables in database \"%s\"\n",
				 old_db->db_name);

	*nmaps = num_maps;
	return maps;
}