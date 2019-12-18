#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ cat_ver; } ;
struct TYPE_21__ {int /*<<< orphan*/  major_version; TYPE_1__ controldata; } ;
struct TYPE_20__ {scalar_t__ check; } ;

/* Variables and functions */
 int GET_MAJOR_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ JSONB_FORMAT_CHANGE_CAT_VER ; 
 int /*<<< orphan*/  check_for_isn_and_int8_passing_mismatch (TYPE_3__*) ; 
 int /*<<< orphan*/  check_for_jsonb_9_4_usage (TYPE_3__*) ; 
 int /*<<< orphan*/  check_for_pg_role_prefix (TYPE_3__*) ; 
 int /*<<< orphan*/  check_for_prepared_transactions (TYPE_3__*) ; 
 int /*<<< orphan*/  check_for_reg_data_type_usage (TYPE_3__*) ; 
 int /*<<< orphan*/  check_for_tables_with_oids (TYPE_3__*) ; 
 int /*<<< orphan*/  check_is_install_user (TYPE_3__*) ; 
 int /*<<< orphan*/  check_proper_datallowconn (TYPE_3__*) ; 
 int /*<<< orphan*/  generate_old_dump () ; 
 int /*<<< orphan*/  get_db_and_rel_infos (TYPE_3__*) ; 
 int /*<<< orphan*/  get_loadable_libraries () ; 
 int /*<<< orphan*/  init_tablespaces () ; 
 int /*<<< orphan*/  new_9_0_populate_pg_largeobject_metadata (TYPE_3__*,int) ; 
 int /*<<< orphan*/  old_11_check_for_sql_identifier_data_type_usage (TYPE_3__*) ; 
 int /*<<< orphan*/  old_9_3_check_for_line_data_type_usage (TYPE_3__*) ; 
 int /*<<< orphan*/  old_9_6_check_for_unknown_data_type_usage (TYPE_3__*) ; 
 int /*<<< orphan*/  old_9_6_invalidate_hash_indexes (TYPE_3__*,int) ; 
 TYPE_3__ old_cluster ; 
 int /*<<< orphan*/  start_postmaster (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stop_postmaster (int) ; 
 TYPE_2__ user_opts ; 

void
check_and_dump_old_cluster(bool live_check)
{
	/* -- OLD -- */

	if (!live_check)
		start_postmaster(&old_cluster, true);

	/* Extract a list of databases and tables from the old cluster */
	get_db_and_rel_infos(&old_cluster);

	init_tablespaces();

	get_loadable_libraries();


	/*
	 * Check for various failure cases
	 */
	check_is_install_user(&old_cluster);
	check_proper_datallowconn(&old_cluster);
	check_for_prepared_transactions(&old_cluster);
	check_for_reg_data_type_usage(&old_cluster);
	check_for_isn_and_int8_passing_mismatch(&old_cluster);

	/*
	 * Pre-PG 12 allowed tables to be declared WITH OIDS, which is not
	 * supported anymore. Verify there are none, iff applicable.
	 */
	if (GET_MAJOR_VERSION(old_cluster.major_version) <= 1100)
		check_for_tables_with_oids(&old_cluster);

	/*
	 * PG 12 changed the 'sql_identifier' type storage to be based on name,
	 * not varchar, which breaks on-disk format for existing data. So we need
	 * to prevent upgrade when used in user objects (tables, indexes, ...).
	 */
	if (GET_MAJOR_VERSION(old_cluster.major_version) <= 1100)
		old_11_check_for_sql_identifier_data_type_usage(&old_cluster);

	/*
	 * Pre-PG 10 allowed tables with 'unknown' type columns and non WAL logged
	 * hash indexes
	 */
	if (GET_MAJOR_VERSION(old_cluster.major_version) <= 906)
	{
		old_9_6_check_for_unknown_data_type_usage(&old_cluster);
		if (user_opts.check)
			old_9_6_invalidate_hash_indexes(&old_cluster, true);
	}

	/* 9.5 and below should not have roles starting with pg_ */
	if (GET_MAJOR_VERSION(old_cluster.major_version) <= 905)
		check_for_pg_role_prefix(&old_cluster);

	if (GET_MAJOR_VERSION(old_cluster.major_version) == 904 &&
		old_cluster.controldata.cat_ver < JSONB_FORMAT_CHANGE_CAT_VER)
		check_for_jsonb_9_4_usage(&old_cluster);

	/* Pre-PG 9.4 had a different 'line' data type internal format */
	if (GET_MAJOR_VERSION(old_cluster.major_version) <= 903)
		old_9_3_check_for_line_data_type_usage(&old_cluster);

	/* Pre-PG 9.0 had no large object permissions */
	if (GET_MAJOR_VERSION(old_cluster.major_version) <= 804)
		new_9_0_populate_pg_largeobject_metadata(&old_cluster, true);

	/*
	 * While not a check option, we do this now because this is the only time
	 * the old server is running.
	 */
	if (!user_opts.check)
		generate_old_dump();

	if (!live_check)
		stop_postmaster(false);
}