#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  scalar_t__ ExecStatusType ;
typedef  TYPE_1__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die_on_query_failure (TYPE_1__*,char const*) ; 

PGresult *
ExecuteSqlQuery(Archive *AHX, const char *query, ExecStatusType status)
{
	ArchiveHandle *AH = (ArchiveHandle *) AHX;
	PGresult   *res;

	res = PQexec(AH->connection, query);
	if (PQresultStatus(res) != status)
		die_on_query_failure(AH, query);
	return res;
}