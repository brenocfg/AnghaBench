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
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecuteSqlQueryForSingleRow (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atooid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Oid
findLastBuiltinOid_V71(Archive *fout)
{
	PGresult   *res;
	Oid			last_oid;

	res = ExecuteSqlQueryForSingleRow(fout,
									  "SELECT datlastsysoid FROM pg_database WHERE datname = current_database()");
	last_oid = atooid(PQgetvalue(res, 0, PQfnumber(res, "datlastsysoid")));
	PQclear(res);

	return last_oid;
}