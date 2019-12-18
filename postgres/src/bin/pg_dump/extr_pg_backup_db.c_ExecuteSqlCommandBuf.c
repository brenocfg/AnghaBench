#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ outputKind; int /*<<< orphan*/  connection; scalar_t__ pgCopyIn; } ;
typedef  TYPE_1__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/  ExecuteSimpleCommands (TYPE_1__*,char const*,size_t) ; 
 int /*<<< orphan*/  ExecuteSqlCommand (TYPE_1__*,char const*,char*) ; 
 scalar_t__ OUTPUT_COPYDATA ; 
 scalar_t__ OUTPUT_OTHERDATA ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 scalar_t__ PQputCopyData (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ pg_malloc (size_t) ; 

int
ExecuteSqlCommandBuf(Archive *AHX, const char *buf, size_t bufLen)
{
	ArchiveHandle *AH = (ArchiveHandle *) AHX;

	if (AH->outputKind == OUTPUT_COPYDATA)
	{
		/*
		 * COPY data.
		 *
		 * We drop the data on the floor if libpq has failed to enter COPY
		 * mode; this allows us to behave reasonably when trying to continue
		 * after an error in a COPY command.
		 */
		if (AH->pgCopyIn &&
			PQputCopyData(AH->connection, buf, bufLen) <= 0)
			fatal("error returned by PQputCopyData: %s",
				  PQerrorMessage(AH->connection));
	}
	else if (AH->outputKind == OUTPUT_OTHERDATA)
	{
		/*
		 * Table data expressed as INSERT commands; or, in old dump files,
		 * BLOB COMMENTS data (which is expressed as COMMENT ON commands).
		 */
		ExecuteSimpleCommands(AH, buf, bufLen);
	}
	else
	{
		/*
		 * General SQL commands; we assume that commands will not be split
		 * across calls.
		 *
		 * In most cases the data passed to us will be a null-terminated
		 * string, but if it's not, we have to add a trailing null.
		 */
		if (buf[bufLen] == '\0')
			ExecuteSqlCommand(AH, buf, "could not execute query");
		else
		{
			char	   *str = (char *) pg_malloc(bufLen + 1);

			memcpy(str, buf, bufLen);
			str[bufLen] = '\0';
			ExecuteSqlCommand(AH, str, "could not execute query");
			free(str);
		}
	}

	return bufLen;
}