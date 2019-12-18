#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * connection; } ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  TYPE_1__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/  ALWAYS_SECURE_SEARCH_PATH_SQL ; 
 int /*<<< orphan*/  ExecuteSqlQueryForSingleRow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ ) ; 
 char* PQdb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 char* PQuser (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _connectDB (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  set_archive_cancel_info (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
ReconnectToServer(ArchiveHandle *AH, const char *dbname, const char *username)
{
	PGconn	   *newConn;
	const char *newdbname;
	const char *newusername;

	if (!dbname)
		newdbname = PQdb(AH->connection);
	else
		newdbname = dbname;

	if (!username)
		newusername = PQuser(AH->connection);
	else
		newusername = username;

	newConn = _connectDB(AH, newdbname, newusername);

	/* Update ArchiveHandle's connCancel before closing old connection */
	set_archive_cancel_info(AH, newConn);

	PQfinish(AH->connection);
	AH->connection = newConn;

	/* Start strict; later phases may override this. */
	PQclear(ExecuteSqlQueryForSingleRow((Archive *) AH,
										ALWAYS_SECURE_SEARCH_PATH_SQL));
}