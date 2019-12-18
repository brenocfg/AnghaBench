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
typedef  int /*<<< orphan*/  namespaceName ;
struct TYPE_2__ {void* tempNamespaceId; } ;
typedef  void* Oid ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_CREATE_TEMP ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AssertState (int) ; 
 int /*<<< orphan*/  BOOTSTRAP_SUPERUSERID ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_READ_ONLY_SQL_TRANSACTION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetCurrentSubTransactionId () ; 
 int /*<<< orphan*/  GetUserId () ; 
 scalar_t__ InvalidSubTransactionId ; 
 scalar_t__ IsParallelWorker () ; 
 int MyBackendId ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 TYPE_1__* MyProc ; 
 int NAMEDATALEN ; 
 void* NamespaceCreate (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OidIsValid (void*) ; 
 scalar_t__ RecoveryInProgress () ; 
 int /*<<< orphan*/  RemoveTempRelations (void*) ; 
 int baseSearchPathValid ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  get_database_name (int /*<<< orphan*/ ) ; 
 void* get_namespace_oid (char*,int) ; 
 void* myTempNamespace ; 
 scalar_t__ myTempNamespaceSubID ; 
 void* myTempToastNamespace ; 
 scalar_t__ pg_database_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
InitTempTableNamespace(void)
{
	char		namespaceName[NAMEDATALEN];
	Oid			namespaceId;
	Oid			toastspaceId;

	Assert(!OidIsValid(myTempNamespace));

	/*
	 * First, do permission check to see if we are authorized to make temp
	 * tables.  We use a nonstandard error message here since "databasename:
	 * permission denied" might be a tad cryptic.
	 *
	 * Note that ACL_CREATE_TEMP rights are rechecked in pg_namespace_aclmask;
	 * that's necessary since current user ID could change during the session.
	 * But there's no need to make the namespace in the first place until a
	 * temp table creation request is made by someone with appropriate rights.
	 */
	if (pg_database_aclcheck(MyDatabaseId, GetUserId(),
							 ACL_CREATE_TEMP) != ACLCHECK_OK)
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied to create temporary tables in database \"%s\"",
						get_database_name(MyDatabaseId))));

	/*
	 * Do not allow a Hot Standby session to make temp tables.  Aside from
	 * problems with modifying the system catalogs, there is a naming
	 * conflict: pg_temp_N belongs to the session with BackendId N on the
	 * master, not to a hot standby session with the same BackendId.  We
	 * should not be able to get here anyway due to XactReadOnly checks, but
	 * let's just make real sure.  Note that this also backstops various
	 * operations that allow XactReadOnly transactions to modify temp tables;
	 * they'd need RecoveryInProgress checks if not for this.
	 */
	if (RecoveryInProgress())
		ereport(ERROR,
				(errcode(ERRCODE_READ_ONLY_SQL_TRANSACTION),
				 errmsg("cannot create temporary tables during recovery")));

	/* Parallel workers can't create temporary tables, either. */
	if (IsParallelWorker())
		ereport(ERROR,
				(errcode(ERRCODE_READ_ONLY_SQL_TRANSACTION),
				 errmsg("cannot create temporary tables during a parallel operation")));

	snprintf(namespaceName, sizeof(namespaceName), "pg_temp_%d", MyBackendId);

	namespaceId = get_namespace_oid(namespaceName, true);
	if (!OidIsValid(namespaceId))
	{
		/*
		 * First use of this temp namespace in this database; create it. The
		 * temp namespaces are always owned by the superuser.  We leave their
		 * permissions at default --- i.e., no access except to superuser ---
		 * to ensure that unprivileged users can't peek at other backends'
		 * temp tables.  This works because the places that access the temp
		 * namespace for my own backend skip permissions checks on it.
		 */
		namespaceId = NamespaceCreate(namespaceName, BOOTSTRAP_SUPERUSERID,
									  true);
		/* Advance command counter to make namespace visible */
		CommandCounterIncrement();
	}
	else
	{
		/*
		 * If the namespace already exists, clean it out (in case the former
		 * owner crashed without doing so).
		 */
		RemoveTempRelations(namespaceId);
	}

	/*
	 * If the corresponding toast-table namespace doesn't exist yet, create
	 * it. (We assume there is no need to clean it out if it does exist, since
	 * dropping a parent table should make its toast table go away.)
	 */
	snprintf(namespaceName, sizeof(namespaceName), "pg_toast_temp_%d",
			 MyBackendId);

	toastspaceId = get_namespace_oid(namespaceName, true);
	if (!OidIsValid(toastspaceId))
	{
		toastspaceId = NamespaceCreate(namespaceName, BOOTSTRAP_SUPERUSERID,
									   true);
		/* Advance command counter to make namespace visible */
		CommandCounterIncrement();
	}

	/*
	 * Okay, we've prepared the temp namespace ... but it's not committed yet,
	 * so all our work could be undone by transaction rollback.  Set flag for
	 * AtEOXact_Namespace to know what to do.
	 */
	myTempNamespace = namespaceId;
	myTempToastNamespace = toastspaceId;

	/*
	 * Mark MyProc as owning this namespace which other processes can use to
	 * decide if a temporary namespace is in use or not.  We assume that
	 * assignment of namespaceId is an atomic operation.  Even if it is not,
	 * the temporary relation which resulted in the creation of this temporary
	 * namespace is still locked until the current transaction commits, and
	 * its pg_namespace row is not visible yet.  However it does not matter:
	 * this flag makes the namespace as being in use, so no objects created on
	 * it would be removed concurrently.
	 */
	MyProc->tempNamespaceId = namespaceId;

	/* It should not be done already. */
	AssertState(myTempNamespaceSubID == InvalidSubTransactionId);
	myTempNamespaceSubID = GetCurrentSubTransactionId();

	baseSearchPathValid = false;	/* need to rebuild list */
}