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
struct TYPE_4__ {int num_old_tablespaces; char** old_tablespaces; } ;
struct TYPE_3__ {int transfer_mode; int jobs; } ;
typedef  int /*<<< orphan*/  DbInfoArr ;

/* Variables and functions */
 int /*<<< orphan*/  PG_REPORT ; 
#define  TRANSFER_MODE_CLONE 130 
#define  TRANSFER_MODE_COPY 129 
#define  TRANSFER_MODE_LINK 128 
 int /*<<< orphan*/  check_ok () ; 
 int /*<<< orphan*/  end_progress_output () ; 
 TYPE_2__ os_info ; 
 int /*<<< orphan*/  parallel_transfer_all_new_dbs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  pg_log (int /*<<< orphan*/ ,char*) ; 
 int reap_child (int) ; 
 TYPE_1__ user_opts ; 

void
transfer_all_new_tablespaces(DbInfoArr *old_db_arr, DbInfoArr *new_db_arr,
							 char *old_pgdata, char *new_pgdata)
{
	switch (user_opts.transfer_mode)
	{
		case TRANSFER_MODE_CLONE:
			pg_log(PG_REPORT, "Cloning user relation files\n");
			break;
		case TRANSFER_MODE_COPY:
			pg_log(PG_REPORT, "Copying user relation files\n");
			break;
		case TRANSFER_MODE_LINK:
			pg_log(PG_REPORT, "Linking user relation files\n");
			break;
	}

	/*
	 * Transferring files by tablespace is tricky because a single database
	 * can use multiple tablespaces.  For non-parallel mode, we just pass a
	 * NULL tablespace path, which matches all tablespaces.  In parallel mode,
	 * we pass the default tablespace and all user-created tablespaces and let
	 * those operations happen in parallel.
	 */
	if (user_opts.jobs <= 1)
		parallel_transfer_all_new_dbs(old_db_arr, new_db_arr, old_pgdata,
									  new_pgdata, NULL);
	else
	{
		int			tblnum;

		/* transfer default tablespace */
		parallel_transfer_all_new_dbs(old_db_arr, new_db_arr, old_pgdata,
									  new_pgdata, old_pgdata);

		for (tblnum = 0; tblnum < os_info.num_old_tablespaces; tblnum++)
			parallel_transfer_all_new_dbs(old_db_arr,
										  new_db_arr,
										  old_pgdata,
										  new_pgdata,
										  os_info.old_tablespaces[tblnum]);
		/* reap all children */
		while (reap_child(true) == true)
			;
	}

	end_progress_output();
	check_ok();

	return;
}