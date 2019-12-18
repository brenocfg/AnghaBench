#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DH ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateFile (char*,char*) ; 
 int DH_CHECK_P_NOT_PRIME ; 
 int DH_CHECK_P_NOT_SAFE_PRIME ; 
 int DH_NOT_SUITABLE_GENERATOR ; 
 scalar_t__ DH_check (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  FreeFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/ * PEM_read_DHparams (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSLerrmessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 

__attribute__((used)) static DH  *
load_dh_file(char *filename, bool isServerStart)
{
	FILE	   *fp;
	DH		   *dh = NULL;
	int			codes;

	/* attempt to open file.  It's not an error if it doesn't exist. */
	if ((fp = AllocateFile(filename, "r")) == NULL)
	{
		ereport(isServerStart ? FATAL : LOG,
				(errcode_for_file_access(),
				 errmsg("could not open DH parameters file \"%s\": %m",
						filename)));
		return NULL;
	}

	dh = PEM_read_DHparams(fp, NULL, NULL, NULL);
	FreeFile(fp);

	if (dh == NULL)
	{
		ereport(isServerStart ? FATAL : LOG,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("could not load DH parameters file: %s",
						SSLerrmessage(ERR_get_error()))));
		return NULL;
	}

	/* make sure the DH parameters are usable */
	if (DH_check(dh, &codes) == 0)
	{
		ereport(isServerStart ? FATAL : LOG,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("invalid DH parameters: %s",
						SSLerrmessage(ERR_get_error()))));
		return NULL;
	}
	if (codes & DH_CHECK_P_NOT_PRIME)
	{
		ereport(isServerStart ? FATAL : LOG,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("invalid DH parameters: p is not prime")));
		return NULL;
	}
	if ((codes & DH_NOT_SUITABLE_GENERATOR) &&
		(codes & DH_CHECK_P_NOT_SAFE_PRIME))
	{
		ereport(isServerStart ? FATAL : LOG,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("invalid DH parameters: neither suitable generator or safe prime")));
		return NULL;
	}

	return dh;
}