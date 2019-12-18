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
struct TYPE_2__ {scalar_t__ datconnlimit; int /*<<< orphan*/  datctype; int /*<<< orphan*/  datcollate; int /*<<< orphan*/  encoding; int /*<<< orphan*/  datallowconn; int /*<<< orphan*/  datname; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_database ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_CONNECT ; 
 scalar_t__ CountDBConnections (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DATABASEOID ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERRCODE_TOO_MANY_CONNECTIONS ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_DATABASE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FATAL ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 char* GetDatabaseEncodingName () ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsAutoVacuumWorkerProcess () ; 
 scalar_t__ IsUnderPostmaster ; 
 int /*<<< orphan*/  LC_COLLATE ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGC_BACKEND ; 
 int /*<<< orphan*/  PGC_INTERNAL ; 
 int /*<<< orphan*/  PGC_S_DYNAMIC_DEFAULT ; 
 int /*<<< orphan*/  PGC_S_OVERRIDE ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetConfigOption (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDatabaseEncoding (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_strxfrm_bug () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,...) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ pg_database_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pg_perm_setlocale (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
CheckMyDatabase(const char *name, bool am_superuser, bool override_allow_connections)
{
	HeapTuple	tup;
	Form_pg_database dbform;
	char	   *collate;
	char	   *ctype;

	/* Fetch our pg_database row normally, via syscache */
	tup = SearchSysCache1(DATABASEOID, ObjectIdGetDatum(MyDatabaseId));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for database %u", MyDatabaseId);
	dbform = (Form_pg_database) GETSTRUCT(tup);

	/* This recheck is strictly paranoia */
	if (strcmp(name, NameStr(dbform->datname)) != 0)
		ereport(FATAL,
				(errcode(ERRCODE_UNDEFINED_DATABASE),
				 errmsg("database \"%s\" has disappeared from pg_database",
						name),
				 errdetail("Database OID %u now seems to belong to \"%s\".",
						   MyDatabaseId, NameStr(dbform->datname))));

	/*
	 * Check permissions to connect to the database.
	 *
	 * These checks are not enforced when in standalone mode, so that there is
	 * a way to recover from disabling all access to all databases, for
	 * example "UPDATE pg_database SET datallowconn = false;".
	 *
	 * We do not enforce them for autovacuum worker processes either.
	 */
	if (IsUnderPostmaster && !IsAutoVacuumWorkerProcess())
	{
		/*
		 * Check that the database is currently allowing connections.
		 */
		if (!dbform->datallowconn && !override_allow_connections)
			ereport(FATAL,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
					 errmsg("database \"%s\" is not currently accepting connections",
							name)));

		/*
		 * Check privilege to connect to the database.  (The am_superuser test
		 * is redundant, but since we have the flag, might as well check it
		 * and save a few cycles.)
		 */
		if (!am_superuser &&
			pg_database_aclcheck(MyDatabaseId, GetUserId(),
								 ACL_CONNECT) != ACLCHECK_OK)
			ereport(FATAL,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("permission denied for database \"%s\"", name),
					 errdetail("User does not have CONNECT privilege.")));

		/*
		 * Check connection limit for this database.
		 *
		 * There is a race condition here --- we create our PGPROC before
		 * checking for other PGPROCs.  If two backends did this at about the
		 * same time, they might both think they were over the limit, while
		 * ideally one should succeed and one fail.  Getting that to work
		 * exactly seems more trouble than it is worth, however; instead we
		 * just document that the connection limit is approximate.
		 */
		if (dbform->datconnlimit >= 0 &&
			!am_superuser &&
			CountDBConnections(MyDatabaseId) > dbform->datconnlimit)
			ereport(FATAL,
					(errcode(ERRCODE_TOO_MANY_CONNECTIONS),
					 errmsg("too many connections for database \"%s\"",
							name)));
	}

	/*
	 * OK, we're golden.  Next to-do item is to save the encoding info out of
	 * the pg_database tuple.
	 */
	SetDatabaseEncoding(dbform->encoding);
	/* Record it as a GUC internal option, too */
	SetConfigOption("server_encoding", GetDatabaseEncodingName(),
					PGC_INTERNAL, PGC_S_OVERRIDE);
	/* If we have no other source of client_encoding, use server encoding */
	SetConfigOption("client_encoding", GetDatabaseEncodingName(),
					PGC_BACKEND, PGC_S_DYNAMIC_DEFAULT);

	/* assign locale variables */
	collate = NameStr(dbform->datcollate);
	ctype = NameStr(dbform->datctype);

	if (pg_perm_setlocale(LC_COLLATE, collate) == NULL)
		ereport(FATAL,
				(errmsg("database locale is incompatible with operating system"),
				 errdetail("The database was initialized with LC_COLLATE \"%s\", "
						   " which is not recognized by setlocale().", collate),
				 errhint("Recreate the database with another locale or install the missing locale.")));

	if (pg_perm_setlocale(LC_CTYPE, ctype) == NULL)
		ereport(FATAL,
				(errmsg("database locale is incompatible with operating system"),
				 errdetail("The database was initialized with LC_CTYPE \"%s\", "
						   " which is not recognized by setlocale().", ctype),
				 errhint("Recreate the database with another locale or install the missing locale.")));

	/* Make the locale settings visible as GUC variables, too */
	SetConfigOption("lc_collate", collate, PGC_INTERNAL, PGC_S_OVERRIDE);
	SetConfigOption("lc_ctype", ctype, PGC_INTERNAL, PGC_S_OVERRIDE);

	check_strxfrm_bug();

	ReleaseSysCache(tup);
}