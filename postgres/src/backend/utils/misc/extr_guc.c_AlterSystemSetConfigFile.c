#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union config_var_val {void* stringval; } ;
struct stat {int dummy; } ;
struct config_generic {scalar_t__ context; int flags; scalar_t__ vartype; } ;
struct TYPE_5__ {char* name; int kind; } ;
struct TYPE_4__ {TYPE_2__* setstmt; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  ConfigVariable ;
typedef  int /*<<< orphan*/  AutoConfTmpFileName ;
typedef  int /*<<< orphan*/  AutoConfFileName ;
typedef  TYPE_1__ AlterSystemStmt ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateFile (char*,char*) ; 
 int /*<<< orphan*/  AutoFileLock ; 
 int BasicOpenFile (char*,int) ; 
 int /*<<< orphan*/  ERRCODE_CANT_CHANGE_RUNTIME_PARAM ; 
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 char* ExtractSetVariableArgs (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeConfigVariables (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeFile (int /*<<< orphan*/ *) ; 
 int GUC_DISALLOW_IN_AUTO_FILE ; 
 int GUC_DISALLOW_IN_FILE ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int MAXPGPATH ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 scalar_t__ PGC_INTERNAL ; 
 scalar_t__ PGC_STRING ; 
 int /*<<< orphan*/  PGC_S_FILE ; 
 char* PG_AUTOCONF_FILENAME ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  ParseConfigFp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
#define  VAR_RESET 131 
#define  VAR_RESET_ALL 130 
#define  VAR_SET_DEFAULT 129 
#define  VAR_SET_VALUE 128 
 int /*<<< orphan*/  close (int volatile) ; 
 int /*<<< orphan*/  durable_rename (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 struct config_generic* find_option (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  parse_and_validate_value (struct config_generic*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union config_var_val*,void**) ; 
 int /*<<< orphan*/  replace_auto_config_value (int /*<<< orphan*/ **,int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  superuser () ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  write_auto_conf_file (int volatile,char*,int /*<<< orphan*/ *) ; 

void
AlterSystemSetConfigFile(AlterSystemStmt *altersysstmt)
{
	char	   *name;
	char	   *value;
	bool		resetall = false;
	ConfigVariable *head = NULL;
	ConfigVariable *tail = NULL;
	volatile int Tmpfd;
	char		AutoConfFileName[MAXPGPATH];
	char		AutoConfTmpFileName[MAXPGPATH];

	if (!superuser())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 (errmsg("must be superuser to execute ALTER SYSTEM command"))));

	/*
	 * Extract statement arguments
	 */
	name = altersysstmt->setstmt->name;

	switch (altersysstmt->setstmt->kind)
	{
		case VAR_SET_VALUE:
			value = ExtractSetVariableArgs(altersysstmt->setstmt);
			break;

		case VAR_SET_DEFAULT:
		case VAR_RESET:
			value = NULL;
			break;

		case VAR_RESET_ALL:
			value = NULL;
			resetall = true;
			break;

		default:
			elog(ERROR, "unrecognized alter system stmt type: %d",
				 altersysstmt->setstmt->kind);
			break;
	}

	/*
	 * Unless it's RESET_ALL, validate the target variable and value
	 */
	if (!resetall)
	{
		struct config_generic *record;

		record = find_option(name, false, ERROR);
		if (record == NULL)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("unrecognized configuration parameter \"%s\"",
							name)));

		/*
		 * Don't allow parameters that can't be set in configuration files to
		 * be set in PG_AUTOCONF_FILENAME file.
		 */
		if ((record->context == PGC_INTERNAL) ||
			(record->flags & GUC_DISALLOW_IN_FILE) ||
			(record->flags & GUC_DISALLOW_IN_AUTO_FILE))
			ereport(ERROR,
					(errcode(ERRCODE_CANT_CHANGE_RUNTIME_PARAM),
					 errmsg("parameter \"%s\" cannot be changed",
							name)));

		/*
		 * If a value is specified, verify that it's sane.
		 */
		if (value)
		{
			union config_var_val newval;
			void	   *newextra = NULL;

			/* Check that it's acceptable for the indicated parameter */
			if (!parse_and_validate_value(record, name, value,
										  PGC_S_FILE, ERROR,
										  &newval, &newextra))
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						 errmsg("invalid value for parameter \"%s\": \"%s\"",
								name, value)));

			if (record->vartype == PGC_STRING && newval.stringval != NULL)
				free(newval.stringval);
			if (newextra)
				free(newextra);

			/*
			 * We must also reject values containing newlines, because the
			 * grammar for config files doesn't support embedded newlines in
			 * string literals.
			 */
			if (strchr(value, '\n'))
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						 errmsg("parameter value for ALTER SYSTEM must not contain a newline")));
		}
	}

	/*
	 * PG_AUTOCONF_FILENAME and its corresponding temporary file are always in
	 * the data directory, so we can reference them by simple relative paths.
	 */
	snprintf(AutoConfFileName, sizeof(AutoConfFileName), "%s",
			 PG_AUTOCONF_FILENAME);
	snprintf(AutoConfTmpFileName, sizeof(AutoConfTmpFileName), "%s.%s",
			 AutoConfFileName,
			 "tmp");

	/*
	 * Only one backend is allowed to operate on PG_AUTOCONF_FILENAME at a
	 * time.  Use AutoFileLock to ensure that.  We must hold the lock while
	 * reading the old file contents.
	 */
	LWLockAcquire(AutoFileLock, LW_EXCLUSIVE);

	/*
	 * If we're going to reset everything, then no need to open or parse the
	 * old file.  We'll just write out an empty list.
	 */
	if (!resetall)
	{
		struct stat st;

		if (stat(AutoConfFileName, &st) == 0)
		{
			/* open old file PG_AUTOCONF_FILENAME */
			FILE	   *infile;

			infile = AllocateFile(AutoConfFileName, "r");
			if (infile == NULL)
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not open file \"%s\": %m",
								AutoConfFileName)));

			/* parse it */
			if (!ParseConfigFp(infile, AutoConfFileName, 0, LOG, &head, &tail))
				ereport(ERROR,
						(errcode(ERRCODE_CONFIG_FILE_ERROR),
						 errmsg("could not parse contents of file \"%s\"",
								AutoConfFileName)));

			FreeFile(infile);
		}

		/*
		 * Now, replace any existing entry with the new value, or add it if
		 * not present.
		 */
		replace_auto_config_value(&head, &tail, name, value);
	}

	/*
	 * To ensure crash safety, first write the new file data to a temp file,
	 * then atomically rename it into place.
	 *
	 * If there is a temp file left over due to a previous crash, it's okay to
	 * truncate and reuse it.
	 */
	Tmpfd = BasicOpenFile(AutoConfTmpFileName,
						  O_CREAT | O_RDWR | O_TRUNC);
	if (Tmpfd < 0)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not open file \"%s\": %m",
						AutoConfTmpFileName)));

	/*
	 * Use a TRY block to clean up the file if we fail.  Since we need a TRY
	 * block anyway, OK to use BasicOpenFile rather than OpenTransientFile.
	 */
	PG_TRY();
	{
		/* Write and sync the new contents to the temporary file */
		write_auto_conf_file(Tmpfd, AutoConfTmpFileName, head);

		/* Close before renaming; may be required on some platforms */
		close(Tmpfd);
		Tmpfd = -1;

		/*
		 * As the rename is atomic operation, if any problem occurs after this
		 * at worst it can lose the parameters set by last ALTER SYSTEM
		 * command.
		 */
		durable_rename(AutoConfTmpFileName, AutoConfFileName, ERROR);
	}
	PG_CATCH();
	{
		/* Close file first, else unlink might fail on some platforms */
		if (Tmpfd >= 0)
			close(Tmpfd);

		/* Unlink, but ignore any error */
		(void) unlink(AutoConfTmpFileName);

		PG_RE_THROW();
	}
	PG_END_TRY();

	FreeConfigVariables(head);

	LWLockRelease(AutoFileLock);
}