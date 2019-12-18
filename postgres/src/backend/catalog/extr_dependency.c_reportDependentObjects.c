#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; int /*<<< orphan*/  const dependee; } ;
struct TYPE_9__ {int numrefs; TYPE_3__* extras; int /*<<< orphan*/ * refs; } ;
struct TYPE_8__ {scalar_t__ len; char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ ObjectAddresses ;
typedef  TYPE_3__ ObjectAddressExtra ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  scalar_t__ DropBehavior ;

/* Variables and functions */
 int DEBUG2 ; 
 int DEPFLAG_AUTO ; 
 int DEPFLAG_EXTENSION ; 
 int DEPFLAG_INTERNAL ; 
 int DEPFLAG_IS_PART ; 
 int DEPFLAG_ORIGINAL ; 
 int DEPFLAG_PARTITION ; 
 int DEPFLAG_SUBOBJECT ; 
 scalar_t__ DROP_CASCADE ; 
 scalar_t__ DROP_RESTRICT ; 
 int /*<<< orphan*/  ERRCODE_DEPENDENT_OBJECTS_STILL_EXIST ; 
 int ERROR ; 
 int LOG ; 
 int MAX_REPORTED_DEPS ; 
 int NOTICE ; 
 int PERFORM_DELETION_QUIETLY ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_1__*,char) ; 
 int client_min_messages ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char*) ; 
 int /*<<< orphan*/  errdetail_log (char*,char*) ; 
 int /*<<< orphan*/  errhint (char*,...) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  errmsg_internal (char*,char*) ; 
 int /*<<< orphan*/  errmsg_plural (char*,char*,int,int) ; 
 char* getObjectDescription (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int log_min_messages ; 
 int /*<<< orphan*/  ngettext (char*,char*,int) ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static void
reportDependentObjects(const ObjectAddresses *targetObjects,
					   DropBehavior behavior,
					   int flags,
					   const ObjectAddress *origObject)
{
	int			msglevel = (flags & PERFORM_DELETION_QUIETLY) ? DEBUG2 : NOTICE;
	bool		ok = true;
	StringInfoData clientdetail;
	StringInfoData logdetail;
	int			numReportedClient = 0;
	int			numNotReportedClient = 0;
	int			i;

	/*
	 * If we need to delete any partition-dependent objects, make sure that
	 * we're deleting at least one of their partition dependencies, too. That
	 * can be detected by checking that we reached them by a PARTITION
	 * dependency at some point.
	 *
	 * We just report the first such object, as in most cases the only way to
	 * trigger this complaint is to explicitly try to delete one partition of
	 * a partitioned object.
	 */
	for (i = 0; i < targetObjects->numrefs; i++)
	{
		const ObjectAddressExtra *extra = &targetObjects->extras[i];

		if ((extra->flags & DEPFLAG_IS_PART) &&
			!(extra->flags & DEPFLAG_PARTITION))
		{
			const ObjectAddress *object = &targetObjects->refs[i];
			char	   *otherObjDesc = getObjectDescription(&extra->dependee);

			ereport(ERROR,
					(errcode(ERRCODE_DEPENDENT_OBJECTS_STILL_EXIST),
					 errmsg("cannot drop %s because %s requires it",
							getObjectDescription(object), otherObjDesc),
					 errhint("You can drop %s instead.", otherObjDesc)));
		}
	}

	/*
	 * If no error is to be thrown, and the msglevel is too low to be shown to
	 * either client or server log, there's no need to do any of the rest of
	 * the work.
	 *
	 * Note: this code doesn't know all there is to be known about elog
	 * levels, but it works for NOTICE and DEBUG2, which are the only values
	 * msglevel can currently have.  We also assume we are running in a normal
	 * operating environment.
	 */
	if (behavior == DROP_CASCADE &&
		msglevel < client_min_messages &&
		(msglevel < log_min_messages || log_min_messages == LOG))
		return;

	/*
	 * We limit the number of dependencies reported to the client to
	 * MAX_REPORTED_DEPS, since client software may not deal well with
	 * enormous error strings.  The server log always gets a full report.
	 */
#define MAX_REPORTED_DEPS 100

	initStringInfo(&clientdetail);
	initStringInfo(&logdetail);

	/*
	 * We process the list back to front (ie, in dependency order not deletion
	 * order), since this makes for a more understandable display.
	 */
	for (i = targetObjects->numrefs - 1; i >= 0; i--)
	{
		const ObjectAddress *obj = &targetObjects->refs[i];
		const ObjectAddressExtra *extra = &targetObjects->extras[i];
		char	   *objDesc;

		/* Ignore the original deletion target(s) */
		if (extra->flags & DEPFLAG_ORIGINAL)
			continue;

		/* Also ignore sub-objects; we'll report the whole object elsewhere */
		if (extra->flags & DEPFLAG_SUBOBJECT)
			continue;

		objDesc = getObjectDescription(obj);

		/*
		 * If, at any stage of the recursive search, we reached the object via
		 * an AUTO, INTERNAL, PARTITION, or EXTENSION dependency, then it's
		 * okay to delete it even in RESTRICT mode.
		 */
		if (extra->flags & (DEPFLAG_AUTO |
							DEPFLAG_INTERNAL |
							DEPFLAG_PARTITION |
							DEPFLAG_EXTENSION))
		{
			/*
			 * auto-cascades are reported at DEBUG2, not msglevel.  We don't
			 * try to combine them with the regular message because the
			 * results are too confusing when client_min_messages and
			 * log_min_messages are different.
			 */
			ereport(DEBUG2,
					(errmsg("drop auto-cascades to %s",
							objDesc)));
		}
		else if (behavior == DROP_RESTRICT)
		{
			char	   *otherDesc = getObjectDescription(&extra->dependee);

			if (numReportedClient < MAX_REPORTED_DEPS)
			{
				/* separate entries with a newline */
				if (clientdetail.len != 0)
					appendStringInfoChar(&clientdetail, '\n');
				appendStringInfo(&clientdetail, _("%s depends on %s"),
								 objDesc, otherDesc);
				numReportedClient++;
			}
			else
				numNotReportedClient++;
			/* separate entries with a newline */
			if (logdetail.len != 0)
				appendStringInfoChar(&logdetail, '\n');
			appendStringInfo(&logdetail, _("%s depends on %s"),
							 objDesc, otherDesc);
			pfree(otherDesc);
			ok = false;
		}
		else
		{
			if (numReportedClient < MAX_REPORTED_DEPS)
			{
				/* separate entries with a newline */
				if (clientdetail.len != 0)
					appendStringInfoChar(&clientdetail, '\n');
				appendStringInfo(&clientdetail, _("drop cascades to %s"),
								 objDesc);
				numReportedClient++;
			}
			else
				numNotReportedClient++;
			/* separate entries with a newline */
			if (logdetail.len != 0)
				appendStringInfoChar(&logdetail, '\n');
			appendStringInfo(&logdetail, _("drop cascades to %s"),
							 objDesc);
		}

		pfree(objDesc);
	}

	if (numNotReportedClient > 0)
		appendStringInfo(&clientdetail, ngettext("\nand %d other object "
												 "(see server log for list)",
												 "\nand %d other objects "
												 "(see server log for list)",
												 numNotReportedClient),
						 numNotReportedClient);

	if (!ok)
	{
		if (origObject)
			ereport(ERROR,
					(errcode(ERRCODE_DEPENDENT_OBJECTS_STILL_EXIST),
					 errmsg("cannot drop %s because other objects depend on it",
							getObjectDescription(origObject)),
					 errdetail("%s", clientdetail.data),
					 errdetail_log("%s", logdetail.data),
					 errhint("Use DROP ... CASCADE to drop the dependent objects too.")));
		else
			ereport(ERROR,
					(errcode(ERRCODE_DEPENDENT_OBJECTS_STILL_EXIST),
					 errmsg("cannot drop desired object(s) because other objects depend on them"),
					 errdetail("%s", clientdetail.data),
					 errdetail_log("%s", logdetail.data),
					 errhint("Use DROP ... CASCADE to drop the dependent objects too.")));
	}
	else if (numReportedClient > 1)
	{
		ereport(msglevel,
		/* translator: %d always has a value larger than 1 */
				(errmsg_plural("drop cascades to %d other object",
							   "drop cascades to %d other objects",
							   numReportedClient + numNotReportedClient,
							   numReportedClient + numNotReportedClient),
				 errdetail("%s", clientdetail.data),
				 errdetail_log("%s", logdetail.data)));
	}
	else if (numReportedClient == 1)
	{
		/* we just use the single item as-is */
		ereport(msglevel,
				(errmsg_internal("%s", clientdetail.data)));
	}

	pfree(clientdetail.data);
	pfree(logdetail.data);
}