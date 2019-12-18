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
struct TYPE_2__ {int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetCancelConn () ; 
 int /*<<< orphan*/  SetCancelConn () ; 
 int /*<<< orphan*/  atooid (char const*) ; 
 int fail_lo_xact (char*,int) ; 
 int /*<<< orphan*/  finish_lo_xact (char*,int) ; 
 int lo_unlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_lo_result (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ pset ; 
 int /*<<< orphan*/  start_lo_xact (char*,int*) ; 

bool
do_lo_unlink(const char *loid_arg)
{
	int			status;
	Oid			loid = atooid(loid_arg);
	bool		own_transaction;

	if (!start_lo_xact("\\lo_unlink", &own_transaction))
		return false;

	SetCancelConn();
	status = lo_unlink(pset.db, loid);
	ResetCancelConn();

	if (status == -1)
	{
		pg_log_info("%s", PQerrorMessage(pset.db));
		return fail_lo_xact("\\lo_unlink", own_transaction);
	}

	if (!finish_lo_xact("\\lo_unlink", own_transaction))
		return false;

	print_lo_result("lo_unlink %u", loid);

	return true;
}