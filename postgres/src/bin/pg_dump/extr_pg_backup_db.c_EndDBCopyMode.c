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
struct TYPE_3__ {int pgCopyIn; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_1__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ ) ; 
 scalar_t__ PQputCopyEnd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_warning (char*,char const*) ; 
 int /*<<< orphan*/  warn_or_exit_horribly (TYPE_1__*,char*,char const*,int /*<<< orphan*/ ) ; 

void
EndDBCopyMode(Archive *AHX, const char *tocEntryTag)
{
	ArchiveHandle *AH = (ArchiveHandle *) AHX;

	if (AH->pgCopyIn)
	{
		PGresult   *res;

		if (PQputCopyEnd(AH->connection, NULL) <= 0)
			fatal("error returned by PQputCopyEnd: %s",
				  PQerrorMessage(AH->connection));

		/* Check command status and return to normal libpq state */
		res = PQgetResult(AH->connection);
		if (PQresultStatus(res) != PGRES_COMMAND_OK)
			warn_or_exit_horribly(AH, "COPY failed for table \"%s\": %s",
								  tocEntryTag, PQerrorMessage(AH->connection));
		PQclear(res);

		/* Do this to ensure we've pumped libpq back to idle state */
		if (PQgetResult(AH->connection) != NULL)
			pg_log_warning("unexpected extra results during COPY of table \"%s\"",
						   tocEntryTag);

		AH->pgCopyIn = false;
	}
}