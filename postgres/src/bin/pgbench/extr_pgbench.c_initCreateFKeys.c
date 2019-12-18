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
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  executeStatement (int /*<<< orphan*/ *,char const* const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int lengthof (char const* const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
initCreateFKeys(PGconn *con)
{
	static const char *const DDLKEYs[] = {
		"alter table pgbench_tellers add constraint pgbench_tellers_bid_fkey foreign key (bid) references pgbench_branches",
		"alter table pgbench_accounts add constraint pgbench_accounts_bid_fkey foreign key (bid) references pgbench_branches",
		"alter table pgbench_history add constraint pgbench_history_bid_fkey foreign key (bid) references pgbench_branches",
		"alter table pgbench_history add constraint pgbench_history_tid_fkey foreign key (tid) references pgbench_tellers",
		"alter table pgbench_history add constraint pgbench_history_aid_fkey foreign key (aid) references pgbench_accounts"
	};
	int			i;

	fprintf(stderr, "creating foreign keys...\n");
	for (i = 0; i < lengthof(DDLKEYs); i++)
	{
		executeStatement(con, DDLKEYs[i]);
	}
}