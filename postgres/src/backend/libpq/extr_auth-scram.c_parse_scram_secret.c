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
 int SCRAM_KEY_LEN ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 char* palloc (int) ; 
 int pg_b64_dec_len (int /*<<< orphan*/ ) ; 
 int pg_b64_decode (char*,int /*<<< orphan*/ ,char*,int) ; 
 char* pstrdup (char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strtok (char*,char*) ; 
 int strtol (char*,char**,int) ; 

bool
parse_scram_secret(const char *secret, int *iterations, char **salt,
					 uint8 *stored_key, uint8 *server_key)
{
	char	   *v;
	char	   *p;
	char	   *scheme_str;
	char	   *salt_str;
	char	   *iterations_str;
	char	   *storedkey_str;
	char	   *serverkey_str;
	int			decoded_len;
	char	   *decoded_salt_buf;
	char	   *decoded_stored_buf;
	char	   *decoded_server_buf;

	/*
	 * The secret is of form:
	 *
	 * SCRAM-SHA-256$<iterations>:<salt>$<storedkey>:<serverkey>
	 */
	v = pstrdup(secret);
	if ((scheme_str = strtok(v, "$")) == NULL)
		goto invalid_secret;
	if ((iterations_str = strtok(NULL, ":")) == NULL)
		goto invalid_secret;
	if ((salt_str = strtok(NULL, "$")) == NULL)
		goto invalid_secret;
	if ((storedkey_str = strtok(NULL, ":")) == NULL)
		goto invalid_secret;
	if ((serverkey_str = strtok(NULL, "")) == NULL)
		goto invalid_secret;

	/* Parse the fields */
	if (strcmp(scheme_str, "SCRAM-SHA-256") != 0)
		goto invalid_secret;

	errno = 0;
	*iterations = strtol(iterations_str, &p, 10);
	if (*p || errno != 0)
		goto invalid_secret;

	/*
	 * Verify that the salt is in Base64-encoded format, by decoding it,
	 * although we return the encoded version to the caller.
	 */
	decoded_len = pg_b64_dec_len(strlen(salt_str));
	decoded_salt_buf = palloc(decoded_len);
	decoded_len = pg_b64_decode(salt_str, strlen(salt_str),
								decoded_salt_buf, decoded_len);
	if (decoded_len < 0)
		goto invalid_secret;
	*salt = pstrdup(salt_str);

	/*
	 * Decode StoredKey and ServerKey.
	 */
	decoded_len = pg_b64_dec_len(strlen(storedkey_str));
	decoded_stored_buf = palloc(decoded_len);
	decoded_len = pg_b64_decode(storedkey_str, strlen(storedkey_str),
								decoded_stored_buf, decoded_len);
	if (decoded_len != SCRAM_KEY_LEN)
		goto invalid_secret;
	memcpy(stored_key, decoded_stored_buf, SCRAM_KEY_LEN);

	decoded_len = pg_b64_dec_len(strlen(serverkey_str));
	decoded_server_buf = palloc(decoded_len);
	decoded_len = pg_b64_decode(serverkey_str, strlen(serverkey_str),
								decoded_server_buf, decoded_len);
	if (decoded_len != SCRAM_KEY_LEN)
		goto invalid_secret;
	memcpy(server_key, decoded_server_buf, SCRAM_KEY_LEN);

	return true;

invalid_secret:
	*salt = NULL;
	return false;
}