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
struct TYPE_5__ {int api_version; } ;
typedef  TYPE_1__ Pg_finfo_record ;
typedef  TYPE_1__* (* PGFInfoFunction ) () ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ lookup_external_function (void*,char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* psprintf (char*,char const*) ; 
 TYPE_1__* stub1 () ; 

const Pg_finfo_record *
fetch_finfo_record(void *filehandle, const char *funcname)
{
	char	   *infofuncname;
	PGFInfoFunction infofunc;
	const Pg_finfo_record *inforec;

	infofuncname = psprintf("pg_finfo_%s", funcname);

	/* Try to look up the info function */
	infofunc = (PGFInfoFunction) lookup_external_function(filehandle,
														  infofuncname);
	if (infofunc == NULL)
	{
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("could not find function information for function \"%s\"",
						funcname),
				 errhint("SQL-callable functions need an accompanying PG_FUNCTION_INFO_V1(funcname).")));
		return NULL;			/* silence compiler */
	}

	/* Found, so call it */
	inforec = (*infofunc) ();

	/* Validate result as best we can */
	if (inforec == NULL)
		elog(ERROR, "null result from info function \"%s\"", infofuncname);
	switch (inforec->api_version)
	{
		case 1:
			/* OK, no additional fields to validate */
			break;
		default:
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("unrecognized API version %d reported by info function \"%s\"",
							inforec->api_version, infofuncname)));
			break;
	}

	pfree(infofuncname);
	return inforec;
}