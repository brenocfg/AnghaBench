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
struct TYPE_2__ {scalar_t__ autocommit; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PSQLexec (char*) ; 
 TYPE_1__ pset ; 

__attribute__((used)) static bool
fail_lo_xact(const char *operation, bool own_transaction)
{
	PGresult   *res;

	if (own_transaction && pset.autocommit)
	{
		/* close out our own xact */
		res = PSQLexec("ROLLBACK");
		PQclear(res);
	}

	return false;				/* always */
}