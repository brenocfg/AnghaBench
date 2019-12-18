#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dbname ;
struct TYPE_8__ {char* databaseId; } ;
struct TYPE_7__ {scalar_t__ canAcceptConnections; } ;
struct TYPE_6__ {char* oid; scalar_t__ dattablespace; int /*<<< orphan*/  datname; } ;
typedef  char* Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_database ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CAC_WAITBACKUP ; 
 int /*<<< orphan*/  CheckDeadLockAlert ; 
 int /*<<< orphan*/  CheckMyDatabase (char*,int,int) ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  CreateAuxProcessResourceOwner () ; 
 int /*<<< orphan*/ * CurrentResourceOwner ; 
 int /*<<< orphan*/  DEADLOCK_TIMEOUT ; 
 int /*<<< orphan*/  DEBUG3 ; 
 scalar_t__ DEFAULTTABLESPACE_OID ; 
 int /*<<< orphan*/  DatabaseRelationId ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_TOO_MANY_CONNECTIONS ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_DATABASE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  EnablePortalManager () ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 char* GetDatabasePath (char*,scalar_t__) ; 
 int /*<<< orphan*/  GetDatabaseTuple (char const*) ; 
 int /*<<< orphan*/  GetDatabaseTupleByOid (char*) ; 
 int /*<<< orphan*/  GetSessionUserId () ; 
 int /*<<< orphan*/  GetTransactionSnapshot () ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HaveNFreeProcs (scalar_t__) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDLE_IN_TRANSACTION_SESSION_TIMEOUT ; 
 int /*<<< orphan*/  IdleInTransactionSessionTimeoutHandler ; 
 int /*<<< orphan*/  InitBufferPoolBackend () ; 
 int /*<<< orphan*/  InitCatalogCache () ; 
 int /*<<< orphan*/  InitPlanCache () ; 
 int /*<<< orphan*/  InitProcessPhase2 () ; 
 int /*<<< orphan*/  InitializeClientEncoding () ; 
 int /*<<< orphan*/  InitializeSearchPath () ; 
 int /*<<< orphan*/  InitializeSession () ; 
 int /*<<< orphan*/  InitializeSessionUserId (char const*,char*) ; 
 int /*<<< orphan*/  InitializeSessionUserIdStandalone () ; 
 scalar_t__ InvalidBackendId ; 
 int /*<<< orphan*/  InvalidateCatalogSnapshot () ; 
 scalar_t__ IsAutoVacuumLauncherProcess () ; 
 scalar_t__ IsAutoVacuumWorkerProcess () ; 
 scalar_t__ IsBackgroundWorker ; 
 scalar_t__ IsBinaryUpgrade ; 
 int IsBootstrapProcessingMode () ; 
 scalar_t__ IsUnderPostmaster ; 
 int /*<<< orphan*/  LOCK_TIMEOUT ; 
 int /*<<< orphan*/  LockSharedObject (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockTimeoutHandler ; 
 scalar_t__ MaxBackends ; 
 scalar_t__ MyBackendId ; 
 char* MyDatabaseId ; 
 scalar_t__ MyDatabaseTableSpace ; 
 TYPE_5__* MyProc ; 
 TYPE_2__* MyProcPort ; 
 int NAMEDATALEN ; 
 char const* NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (char*) ; 
 int /*<<< orphan*/  PerformAuthentication (TYPE_2__*) ; 
 long PostAuthDelay ; 
 int /*<<< orphan*/  ProcSignalInit (scalar_t__) ; 
 int /*<<< orphan*/  RecoveryInProgress () ; 
 int /*<<< orphan*/  RegisterTimeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationCacheInitialize () ; 
 int /*<<< orphan*/  RelationCacheInitializePhase2 () ; 
 int /*<<< orphan*/  RelationCacheInitializePhase3 () ; 
 int /*<<< orphan*/  ReleaseAuxProcessResources (int) ; 
 scalar_t__ ReservedBackends ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  STATEMENT_TIMEOUT ; 
 int /*<<< orphan*/  SetCurrentStatementStartTimestamp () ; 
 int /*<<< orphan*/  SetDatabasePath (char*) ; 
 int /*<<< orphan*/  SharedInvalBackendInit (int) ; 
 int /*<<< orphan*/  ShutdownPostgres ; 
 int /*<<< orphan*/  ShutdownXLOG ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  StartupXLOG () ; 
 int /*<<< orphan*/  StatementTimeoutHandler ; 
 char* TemplateDbOid ; 
 int /*<<< orphan*/  ThereIsAtLeastOneRole () ; 
 int /*<<< orphan*/  ValidatePgVersion (char*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  XACT_READ_COMMITTED ; 
 int /*<<< orphan*/  XactIsoLevel ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  am_db_walsender ; 
 scalar_t__ am_walsender ; 
 int /*<<< orphan*/  before_shmem_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errdetail (char*,...) ; 
 int /*<<< orphan*/  errhint (char*,char const*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  has_rolreplication (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_acl () ; 
 int /*<<< orphan*/  on_shmem_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_usleep (long) ; 
 int /*<<< orphan*/  pgstat_bestart () ; 
 int /*<<< orphan*/  pgstat_initialize () ; 
 int /*<<< orphan*/  process_settings (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_startup_options (TYPE_2__*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int superuser () ; 

void
InitPostgres(const char *in_dbname, Oid dboid, const char *username,
			 Oid useroid, char *out_dbname, bool override_allow_connections)
{
	bool		bootstrap = IsBootstrapProcessingMode();
	bool		am_superuser;
	char	   *fullpath;
	char		dbname[NAMEDATALEN];

	elog(DEBUG3, "InitPostgres");

	/*
	 * Add my PGPROC struct to the ProcArray.
	 *
	 * Once I have done this, I am visible to other backends!
	 */
	InitProcessPhase2();

	/*
	 * Initialize my entry in the shared-invalidation manager's array of
	 * per-backend data.
	 *
	 * Sets up MyBackendId, a unique backend identifier.
	 */
	MyBackendId = InvalidBackendId;

	SharedInvalBackendInit(false);

	if (MyBackendId > MaxBackends || MyBackendId <= 0)
		elog(FATAL, "bad backend ID: %d", MyBackendId);

	/* Now that we have a BackendId, we can participate in ProcSignal */
	ProcSignalInit(MyBackendId);

	/*
	 * Also set up timeout handlers needed for backend operation.  We need
	 * these in every case except bootstrap.
	 */
	if (!bootstrap)
	{
		RegisterTimeout(DEADLOCK_TIMEOUT, CheckDeadLockAlert);
		RegisterTimeout(STATEMENT_TIMEOUT, StatementTimeoutHandler);
		RegisterTimeout(LOCK_TIMEOUT, LockTimeoutHandler);
		RegisterTimeout(IDLE_IN_TRANSACTION_SESSION_TIMEOUT,
						IdleInTransactionSessionTimeoutHandler);
	}

	/*
	 * bufmgr needs another initialization call too
	 */
	InitBufferPoolBackend();

	/*
	 * Initialize local process's access to XLOG.
	 */
	if (IsUnderPostmaster)
	{
		/*
		 * The postmaster already started the XLOG machinery, but we need to
		 * call InitXLOGAccess(), if the system isn't in hot-standby mode.
		 * This is handled by calling RecoveryInProgress and ignoring the
		 * result.
		 */
		(void) RecoveryInProgress();
	}
	else
	{
		/*
		 * We are either a bootstrap process or a standalone backend. Either
		 * way, start up the XLOG machinery, and register to have it closed
		 * down at exit.
		 *
		 * We don't yet have an aux-process resource owner, but StartupXLOG
		 * and ShutdownXLOG will need one.  Hence, create said resource owner
		 * (and register a callback to clean it up after ShutdownXLOG runs).
		 */
		CreateAuxProcessResourceOwner();

		StartupXLOG();
		/* Release (and warn about) any buffer pins leaked in StartupXLOG */
		ReleaseAuxProcessResources(true);
		/* Reset CurrentResourceOwner to nothing for the moment */
		CurrentResourceOwner = NULL;

		on_shmem_exit(ShutdownXLOG, 0);
	}

	/*
	 * Initialize the relation cache and the system catalog caches.  Note that
	 * no catalog access happens here; we only set up the hashtable structure.
	 * We must do this before starting a transaction because transaction abort
	 * would try to touch these hashtables.
	 */
	RelationCacheInitialize();
	InitCatalogCache();
	InitPlanCache();

	/* Initialize portal manager */
	EnablePortalManager();

	/* Initialize stats collection --- must happen before first xact */
	if (!bootstrap)
		pgstat_initialize();

	/*
	 * Load relcache entries for the shared system catalogs.  This must create
	 * at least entries for pg_database and catalogs used for authentication.
	 */
	RelationCacheInitializePhase2();

	/*
	 * Set up process-exit callback to do pre-shutdown cleanup.  This is the
	 * first before_shmem_exit callback we register; thus, this will be the
	 * last thing we do before low-level modules like the buffer manager begin
	 * to close down.  We need to have this in place before we begin our first
	 * transaction --- if we fail during the initialization transaction, as is
	 * entirely possible, we need the AbortTransaction call to clean up.
	 */
	before_shmem_exit(ShutdownPostgres, 0);

	/* The autovacuum launcher is done here */
	if (IsAutoVacuumLauncherProcess())
	{
		/* report this backend in the PgBackendStatus array */
		pgstat_bestart();

		return;
	}

	/*
	 * Start a new transaction here before first access to db, and get a
	 * snapshot.  We don't have a use for the snapshot itself, but we're
	 * interested in the secondary effect that it sets RecentGlobalXmin. (This
	 * is critical for anything that reads heap pages, because HOT may decide
	 * to prune them even if the process doesn't attempt to modify any
	 * tuples.)
	 */
	if (!bootstrap)
	{
		/* statement_timestamp must be set for timeouts to work correctly */
		SetCurrentStatementStartTimestamp();
		StartTransactionCommand();

		/*
		 * transaction_isolation will have been set to the default by the
		 * above.  If the default is "serializable", and we are in hot
		 * standby, we will fail if we don't change it to something lower.
		 * Fortunately, "read committed" is plenty good enough.
		 */
		XactIsoLevel = XACT_READ_COMMITTED;

		(void) GetTransactionSnapshot();
	}

	/*
	 * Perform client authentication if necessary, then figure out our
	 * postgres user ID, and see if we are a superuser.
	 *
	 * In standalone mode and in autovacuum worker processes, we use a fixed
	 * ID, otherwise we figure it out from the authenticated user name.
	 */
	if (bootstrap || IsAutoVacuumWorkerProcess())
	{
		InitializeSessionUserIdStandalone();
		am_superuser = true;
	}
	else if (!IsUnderPostmaster)
	{
		InitializeSessionUserIdStandalone();
		am_superuser = true;
		if (!ThereIsAtLeastOneRole())
			ereport(WARNING,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("no roles are defined in this database system"),
					 errhint("You should immediately run CREATE USER \"%s\" SUPERUSER;.",
							 username != NULL ? username : "postgres")));
	}
	else if (IsBackgroundWorker)
	{
		if (username == NULL && !OidIsValid(useroid))
		{
			InitializeSessionUserIdStandalone();
			am_superuser = true;
		}
		else
		{
			InitializeSessionUserId(username, useroid);
			am_superuser = superuser();
		}
	}
	else
	{
		/* normal multiuser case */
		Assert(MyProcPort != NULL);
		PerformAuthentication(MyProcPort);
		InitializeSessionUserId(username, useroid);
		am_superuser = superuser();
	}

	/*
	 * If we're trying to shut down, only superusers can connect, and new
	 * replication connections are not allowed.
	 */
	if ((!am_superuser || am_walsender) &&
		MyProcPort != NULL &&
		MyProcPort->canAcceptConnections == CAC_WAITBACKUP)
	{
		if (am_walsender)
			ereport(FATAL,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("new replication connections are not allowed during database shutdown")));
		else
			ereport(FATAL,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("must be superuser to connect during database shutdown")));
	}

	/*
	 * Binary upgrades only allowed super-user connections
	 */
	if (IsBinaryUpgrade && !am_superuser)
	{
		ereport(FATAL,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("must be superuser to connect in binary upgrade mode")));
	}

	/*
	 * The last few connection slots are reserved for superusers.  Replication
	 * connections are drawn from slots reserved with max_wal_senders and not
	 * limited by max_connections or superuser_reserved_connections.
	 */
	if (!am_superuser && !am_walsender &&
		ReservedBackends > 0 &&
		!HaveNFreeProcs(ReservedBackends))
		ereport(FATAL,
				(errcode(ERRCODE_TOO_MANY_CONNECTIONS),
				 errmsg("remaining connection slots are reserved for non-replication superuser connections")));

	/* Check replication permissions needed for walsender processes. */
	if (am_walsender)
	{
		Assert(!bootstrap);

		if (!superuser() && !has_rolreplication(GetUserId()))
			ereport(FATAL,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("must be superuser or replication role to start walsender")));
	}

	/*
	 * If this is a plain walsender only supporting physical replication, we
	 * don't want to connect to any particular database. Just finish the
	 * backend startup by processing any options from the startup packet, and
	 * we're done.
	 */
	if (am_walsender && !am_db_walsender)
	{
		/* process any options passed in the startup packet */
		if (MyProcPort != NULL)
			process_startup_options(MyProcPort, am_superuser);

		/* Apply PostAuthDelay as soon as we've read all options */
		if (PostAuthDelay > 0)
			pg_usleep(PostAuthDelay * 1000000L);

		/* initialize client encoding */
		InitializeClientEncoding();

		/* report this backend in the PgBackendStatus array */
		pgstat_bestart();

		/* close the transaction we started above */
		CommitTransactionCommand();

		return;
	}

	/*
	 * Set up the global variables holding database id and default tablespace.
	 * But note we won't actually try to touch the database just yet.
	 *
	 * We take a shortcut in the bootstrap case, otherwise we have to look up
	 * the db's entry in pg_database.
	 */
	if (bootstrap)
	{
		MyDatabaseId = TemplateDbOid;
		MyDatabaseTableSpace = DEFAULTTABLESPACE_OID;
	}
	else if (in_dbname != NULL)
	{
		HeapTuple	tuple;
		Form_pg_database dbform;

		tuple = GetDatabaseTuple(in_dbname);
		if (!HeapTupleIsValid(tuple))
			ereport(FATAL,
					(errcode(ERRCODE_UNDEFINED_DATABASE),
					 errmsg("database \"%s\" does not exist", in_dbname)));
		dbform = (Form_pg_database) GETSTRUCT(tuple);
		MyDatabaseId = dbform->oid;
		MyDatabaseTableSpace = dbform->dattablespace;
		/* take database name from the caller, just for paranoia */
		strlcpy(dbname, in_dbname, sizeof(dbname));
	}
	else if (OidIsValid(dboid))
	{
		/* caller specified database by OID */
		HeapTuple	tuple;
		Form_pg_database dbform;

		tuple = GetDatabaseTupleByOid(dboid);
		if (!HeapTupleIsValid(tuple))
			ereport(FATAL,
					(errcode(ERRCODE_UNDEFINED_DATABASE),
					 errmsg("database %u does not exist", dboid)));
		dbform = (Form_pg_database) GETSTRUCT(tuple);
		MyDatabaseId = dbform->oid;
		MyDatabaseTableSpace = dbform->dattablespace;
		Assert(MyDatabaseId == dboid);
		strlcpy(dbname, NameStr(dbform->datname), sizeof(dbname));
		/* pass the database name back to the caller */
		if (out_dbname)
			strcpy(out_dbname, dbname);
	}
	else
	{
		/*
		 * If this is a background worker not bound to any particular
		 * database, we're done now.  Everything that follows only makes sense
		 * if we are bound to a specific database.  We do need to close the
		 * transaction we started before returning.
		 */
		if (!bootstrap)
		{
			pgstat_bestart();
			CommitTransactionCommand();
		}
		return;
	}

	/*
	 * Now, take a writer's lock on the database we are trying to connect to.
	 * If there is a concurrently running DROP DATABASE on that database, this
	 * will block us until it finishes (and has committed its update of
	 * pg_database).
	 *
	 * Note that the lock is not held long, only until the end of this startup
	 * transaction.  This is OK since we will advertise our use of the
	 * database in the ProcArray before dropping the lock (in fact, that's the
	 * next thing to do).  Anyone trying a DROP DATABASE after this point will
	 * see us in the array once they have the lock.  Ordering is important for
	 * this because we don't want to advertise ourselves as being in this
	 * database until we have the lock; otherwise we create what amounts to a
	 * deadlock with CountOtherDBBackends().
	 *
	 * Note: use of RowExclusiveLock here is reasonable because we envision
	 * our session as being a concurrent writer of the database.  If we had a
	 * way of declaring a session as being guaranteed-read-only, we could use
	 * AccessShareLock for such sessions and thereby not conflict against
	 * CREATE DATABASE.
	 */
	if (!bootstrap)
		LockSharedObject(DatabaseRelationId, MyDatabaseId, 0,
						 RowExclusiveLock);

	/*
	 * Now we can mark our PGPROC entry with the database ID.
	 *
	 * We assume this is an atomic store so no lock is needed; though actually
	 * things would work fine even if it weren't atomic.  Anyone searching the
	 * ProcArray for this database's ID should hold the database lock, so they
	 * would not be executing concurrently with this store.  A process looking
	 * for another database's ID could in theory see a chance match if it read
	 * a partially-updated databaseId value; but as long as all such searches
	 * wait and retry, as in CountOtherDBBackends(), they will certainly see
	 * the correct value on their next try.
	 */
	MyProc->databaseId = MyDatabaseId;

	/*
	 * We established a catalog snapshot while reading pg_authid and/or
	 * pg_database; but until we have set up MyDatabaseId, we won't react to
	 * incoming sinval messages for unshared catalogs, so we won't realize it
	 * if the snapshot has been invalidated.  Assume it's no good anymore.
	 */
	InvalidateCatalogSnapshot();

	/*
	 * Recheck pg_database to make sure the target database hasn't gone away.
	 * If there was a concurrent DROP DATABASE, this ensures we will die
	 * cleanly without creating a mess.
	 */
	if (!bootstrap)
	{
		HeapTuple	tuple;

		tuple = GetDatabaseTuple(dbname);
		if (!HeapTupleIsValid(tuple) ||
			MyDatabaseId != ((Form_pg_database) GETSTRUCT(tuple))->oid ||
			MyDatabaseTableSpace != ((Form_pg_database) GETSTRUCT(tuple))->dattablespace)
			ereport(FATAL,
					(errcode(ERRCODE_UNDEFINED_DATABASE),
					 errmsg("database \"%s\" does not exist", dbname),
					 errdetail("It seems to have just been dropped or renamed.")));
	}

	/*
	 * Now we should be able to access the database directory safely. Verify
	 * it's there and looks reasonable.
	 */
	fullpath = GetDatabasePath(MyDatabaseId, MyDatabaseTableSpace);

	if (!bootstrap)
	{
		if (access(fullpath, F_OK) == -1)
		{
			if (errno == ENOENT)
				ereport(FATAL,
						(errcode(ERRCODE_UNDEFINED_DATABASE),
						 errmsg("database \"%s\" does not exist",
								dbname),
						 errdetail("The database subdirectory \"%s\" is missing.",
								   fullpath)));
			else
				ereport(FATAL,
						(errcode_for_file_access(),
						 errmsg("could not access directory \"%s\": %m",
								fullpath)));
		}

		ValidatePgVersion(fullpath);
	}

	SetDatabasePath(fullpath);

	/*
	 * It's now possible to do real access to the system catalogs.
	 *
	 * Load relcache entries for the system catalogs.  This must create at
	 * least the minimum set of "nailed-in" cache entries.
	 */
	RelationCacheInitializePhase3();

	/* set up ACL framework (so CheckMyDatabase can check permissions) */
	initialize_acl();

	/*
	 * Re-read the pg_database row for our database, check permissions and set
	 * up database-specific GUC settings.  We can't do this until all the
	 * database-access infrastructure is up.  (Also, it wants to know if the
	 * user is a superuser, so the above stuff has to happen first.)
	 */
	if (!bootstrap)
		CheckMyDatabase(dbname, am_superuser, override_allow_connections);

	/*
	 * Now process any command-line switches and any additional GUC variable
	 * settings passed in the startup packet.   We couldn't do this before
	 * because we didn't know if client is a superuser.
	 */
	if (MyProcPort != NULL)
		process_startup_options(MyProcPort, am_superuser);

	/* Process pg_db_role_setting options */
	process_settings(MyDatabaseId, GetSessionUserId());

	/* Apply PostAuthDelay as soon as we've read all options */
	if (PostAuthDelay > 0)
		pg_usleep(PostAuthDelay * 1000000L);

	/*
	 * Initialize various default states that can't be set up until we've
	 * selected the active user and gotten the right GUC settings.
	 */

	/* set default namespace search path */
	InitializeSearchPath();

	/* initialize client encoding */
	InitializeClientEncoding();

	/* Initialize this backend's session state. */
	InitializeSession();

	/* report this backend in the PgBackendStatus array */
	if (!bootstrap)
		pgstat_bestart();

	/* close the transaction we started above */
	if (!bootstrap)
		CommitTransactionCommand();
}