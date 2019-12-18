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
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ pg_saslprep_rc ;

/* Variables and functions */
 int /*<<< orphan*/  LOG ; 
 scalar_t__ SASLPREP_SUCCESS ; 
 int SCRAM_KEY_LEN ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 char* palloc (int) ; 
 int /*<<< orphan*/  parse_scram_secret (char const*,int*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int pg_b64_dec_len (int /*<<< orphan*/ ) ; 
 int pg_b64_decode (char*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ pg_saslprep (char const*,char**) ; 
 int /*<<< orphan*/  scram_SaltedPassword (char const*,char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scram_ServerKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 

bool
scram_verify_plain_password(const char *username, const char *password,
							const char *secret)
{
	char	   *encoded_salt;
	char	   *salt;
	int			saltlen;
	int			iterations;
	uint8		salted_password[SCRAM_KEY_LEN];
	uint8		stored_key[SCRAM_KEY_LEN];
	uint8		server_key[SCRAM_KEY_LEN];
	uint8		computed_key[SCRAM_KEY_LEN];
	char	   *prep_password;
	pg_saslprep_rc rc;

	if (!parse_scram_secret(secret, &iterations, &encoded_salt,
							  stored_key, server_key))
	{
		/*
		 * The password looked like a SCRAM secret, but could not be parsed.
		 */
		ereport(LOG,
				(errmsg("invalid SCRAM secret for user \"%s\"", username)));
		return false;
	}

	saltlen = pg_b64_dec_len(strlen(encoded_salt));
	salt = palloc(saltlen);
	saltlen = pg_b64_decode(encoded_salt, strlen(encoded_salt), salt,
							saltlen);
	if (saltlen < 0)
	{
		ereport(LOG,
				(errmsg("invalid SCRAM secret for user \"%s\"", username)));
		return false;
	}

	/* Normalize the password */
	rc = pg_saslprep(password, &prep_password);
	if (rc == SASLPREP_SUCCESS)
		password = prep_password;

	/* Compute Server Key based on the user-supplied plaintext password */
	scram_SaltedPassword(password, salt, saltlen, iterations, salted_password);
	scram_ServerKey(salted_password, computed_key);

	if (prep_password)
		pfree(prep_password);

	/*
	 * Compare the secret's Server Key with the one computed from the
	 * user-supplied password.
	 */
	return memcmp(computed_key, server_key, SCRAM_KEY_LEN) == 0;
}