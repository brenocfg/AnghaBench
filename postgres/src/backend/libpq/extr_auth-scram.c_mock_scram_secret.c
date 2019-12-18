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
 int /*<<< orphan*/  ERROR ; 
 int SCRAM_DEFAULT_ITERATIONS ; 
 int /*<<< orphan*/  SCRAM_DEFAULT_SALT_LEN ; 
 int /*<<< orphan*/  SCRAM_KEY_LEN ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int pg_b64_enc_len (int /*<<< orphan*/ ) ; 
 int pg_b64_encode (char*,int /*<<< orphan*/ ,char*,int) ; 
 char* scram_mock_salt (char const*) ; 

__attribute__((used)) static void
mock_scram_secret(const char *username, int *iterations, char **salt,
					uint8 *stored_key, uint8 *server_key)
{
	char	   *raw_salt;
	char	   *encoded_salt;
	int			encoded_len;

	/* Generate deterministic salt */
	raw_salt = scram_mock_salt(username);

	encoded_len = pg_b64_enc_len(SCRAM_DEFAULT_SALT_LEN);
	/* don't forget the zero-terminator */
	encoded_salt = (char *) palloc(encoded_len + 1);
	encoded_len = pg_b64_encode(raw_salt, SCRAM_DEFAULT_SALT_LEN, encoded_salt,
								encoded_len);

	/*
	 * Note that we cannot reveal any information to an attacker here so the
	 * error message needs to remain generic.  This should never fail anyway
	 * as the salt generated for mock authentication uses the cluster's nonce
	 * value.
	 */
	if (encoded_len < 0)
		elog(ERROR, "could not encode salt");
	encoded_salt[encoded_len] = '\0';

	*salt = encoded_salt;
	*iterations = SCRAM_DEFAULT_ITERATIONS;

	/* StoredKey and ServerKey are not used in a doomed authentication */
	memset(stored_key, 0, SCRAM_KEY_LEN);
	memset(server_key, 0, SCRAM_KEY_LEN);
}