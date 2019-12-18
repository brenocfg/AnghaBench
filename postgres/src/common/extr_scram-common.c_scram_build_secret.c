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

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int SCRAM_DEFAULT_ITERATIONS ; 
 int SCRAM_KEY_LEN ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 char* palloc (int) ; 
 int pg_b64_enc_len (int) ; 
 int pg_b64_encode (char const*,int,char*,int) ; 
 int /*<<< orphan*/  scram_ClientKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scram_H (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scram_SaltedPassword (char const*,char const*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scram_ServerKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 
 int strlen (char*) ; 

char *
scram_build_secret(const char *salt, int saltlen, int iterations,
					 const char *password)
{
	uint8		salted_password[SCRAM_KEY_LEN];
	uint8		stored_key[SCRAM_KEY_LEN];
	uint8		server_key[SCRAM_KEY_LEN];
	char	   *result;
	char	   *p;
	int			maxlen;
	int			encoded_salt_len;
	int			encoded_stored_len;
	int			encoded_server_len;
	int			encoded_result;

	if (iterations <= 0)
		iterations = SCRAM_DEFAULT_ITERATIONS;

	/* Calculate StoredKey and ServerKey */
	scram_SaltedPassword(password, salt, saltlen, iterations,
						 salted_password);
	scram_ClientKey(salted_password, stored_key);
	scram_H(stored_key, SCRAM_KEY_LEN, stored_key);

	scram_ServerKey(salted_password, server_key);

	/*----------
	 * The format is:
	 * SCRAM-SHA-256$<iteration count>:<salt>$<StoredKey>:<ServerKey>
	 *----------
	 */
	encoded_salt_len = pg_b64_enc_len(saltlen);
	encoded_stored_len = pg_b64_enc_len(SCRAM_KEY_LEN);
	encoded_server_len = pg_b64_enc_len(SCRAM_KEY_LEN);

	maxlen = strlen("SCRAM-SHA-256") + 1
		+ 10 + 1				/* iteration count */
		+ encoded_salt_len + 1	/* Base64-encoded salt */
		+ encoded_stored_len + 1	/* Base64-encoded StoredKey */
		+ encoded_server_len + 1;	/* Base64-encoded ServerKey */

#ifdef FRONTEND
	result = malloc(maxlen);
	if (!result)
		return NULL;
#else
	result = palloc(maxlen);
#endif

	p = result + sprintf(result, "SCRAM-SHA-256$%d:", iterations);

	/* salt */
	encoded_result = pg_b64_encode(salt, saltlen, p, encoded_salt_len);
	if (encoded_result < 0)
	{
#ifdef FRONTEND
		free(result);
		return NULL;
#else
		elog(ERROR, "could not encode salt");
#endif
	}
	p += encoded_result;
	*(p++) = '$';

	/* stored key */
	encoded_result = pg_b64_encode((char *) stored_key, SCRAM_KEY_LEN, p,
								   encoded_stored_len);
	if (encoded_result < 0)
	{
#ifdef FRONTEND
		free(result);
		return NULL;
#else
		elog(ERROR, "could not encode stored key");
#endif
	}

	p += encoded_result;
	*(p++) = ':';

	/* server key */
	encoded_result = pg_b64_encode((char *) server_key, SCRAM_KEY_LEN, p,
								   encoded_server_len);
	if (encoded_result < 0)
	{
#ifdef FRONTEND
		free(result);
		return NULL;
#else
		elog(ERROR, "could not encode server key");
#endif
	}

	p += encoded_result;
	*(p++) = '\0';

	Assert(p - result <= maxlen);

	return result;
}