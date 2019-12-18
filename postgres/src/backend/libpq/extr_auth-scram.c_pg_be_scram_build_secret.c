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
typedef  scalar_t__ pg_saslprep_rc ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ SASLPREP_SUCCESS ; 
 int /*<<< orphan*/  SCRAM_DEFAULT_ITERATIONS ; 
 int SCRAM_DEFAULT_SALT_LEN ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 scalar_t__ pg_saslprep (char const*,char**) ; 
 int /*<<< orphan*/  pg_strong_random (char*,int) ; 
 char* scram_build_secret (char*,int,int /*<<< orphan*/ ,char const*) ; 

char *
pg_be_scram_build_secret(const char *password)
{
	char	   *prep_password;
	pg_saslprep_rc rc;
	char		saltbuf[SCRAM_DEFAULT_SALT_LEN];
	char	   *result;

	/*
	 * Normalize the password with SASLprep.  If that doesn't work, because
	 * the password isn't valid UTF-8 or contains prohibited characters, just
	 * proceed with the original password.  (See comments at top of file.)
	 */
	rc = pg_saslprep(password, &prep_password);
	if (rc == SASLPREP_SUCCESS)
		password = (const char *) prep_password;

	/* Generate random salt */
	if (!pg_strong_random(saltbuf, SCRAM_DEFAULT_SALT_LEN))
		ereport(ERROR,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("could not generate random salt")));

	result = scram_build_secret(saltbuf, SCRAM_DEFAULT_SALT_LEN,
								  SCRAM_DEFAULT_ITERATIONS, password);

	if (prep_password)
		pfree(prep_password);

	return result;
}