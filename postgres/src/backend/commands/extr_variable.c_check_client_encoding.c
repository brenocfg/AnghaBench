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
typedef  int /*<<< orphan*/  GucSource ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  GUC_check_errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUC_check_errdetail (char*,...) ; 
 int /*<<< orphan*/  GetDatabaseEncodingName () ; 
 scalar_t__ IsTransactionState () ; 
 scalar_t__ PrepareClientEncoding (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* malloc (int) ; 
 char* pg_encoding_to_char (int) ; 
 int pg_valid_client_encoding (char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* strdup (char const*) ; 

bool
check_client_encoding(char **newval, void **extra, GucSource source)
{
	int			encoding;
	const char *canonical_name;

	/* Look up the encoding by name */
	encoding = pg_valid_client_encoding(*newval);
	if (encoding < 0)
		return false;

	/* Get the canonical name (no aliases, uniform case) */
	canonical_name = pg_encoding_to_char(encoding);

	/*
	 * If we are not within a transaction then PrepareClientEncoding will not
	 * be able to look up the necessary conversion procs.  If we are still
	 * starting up, it will return "OK" anyway, and InitializeClientEncoding
	 * will fix things once initialization is far enough along.  After
	 * startup, we'll fail.  This would only happen if someone tries to change
	 * client_encoding in postgresql.conf and then SIGHUP existing sessions.
	 * It seems like a bad idea for client_encoding to change that way anyhow,
	 * so we don't go out of our way to support it.
	 *
	 * Note: in the postmaster, or any other process that never calls
	 * InitializeClientEncoding, PrepareClientEncoding will always succeed,
	 * and so will SetClientEncoding; but they won't do anything, which is OK.
	 */
	if (PrepareClientEncoding(encoding) < 0)
	{
		if (IsTransactionState())
		{
			/* Must be a genuine no-such-conversion problem */
			GUC_check_errcode(ERRCODE_FEATURE_NOT_SUPPORTED);
			GUC_check_errdetail("Conversion between %s and %s is not supported.",
								canonical_name,
								GetDatabaseEncodingName());
		}
		else
		{
			/* Provide a useful complaint */
			GUC_check_errdetail("Cannot change \"client_encoding\" now.");
		}
		return false;
	}

	/*
	 * Replace the user-supplied string with the encoding's canonical name.
	 * This gets rid of aliases and case-folding variations.
	 *
	 * XXX Although canonicalizing seems like a good idea in the abstract, it
	 * breaks pre-9.1 JDBC drivers, which expect that if they send "UNICODE"
	 * as the client_encoding setting then it will read back the same way. As
	 * a workaround, don't replace the string if it's "UNICODE".  Remove that
	 * hack when pre-9.1 JDBC drivers are no longer in use.
	 */
	if (strcmp(*newval, canonical_name) != 0 &&
		strcmp(*newval, "UNICODE") != 0)
	{
		free(*newval);
		*newval = strdup(canonical_name);
		if (!*newval)
			return false;
	}

	/*
	 * Save the encoding's ID in *extra, for use by assign_client_encoding.
	 */
	*extra = malloc(sizeof(int));
	if (!*extra)
		return false;
	*((int *) *extra) = encoding;

	return true;
}