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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  scram_HMAC_ctx ;

/* Variables and functions */
 int SCRAM_KEY_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pg_hton32 (int) ; 
 int /*<<< orphan*/  scram_HMAC_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scram_HMAC_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scram_HMAC_update (int /*<<< orphan*/ *,char const*,int) ; 
 int strlen (char const*) ; 

void
scram_SaltedPassword(const char *password,
					 const char *salt, int saltlen, int iterations,
					 uint8 *result)
{
	int			password_len = strlen(password);
	uint32		one = pg_hton32(1);
	int			i,
				j;
	uint8		Ui[SCRAM_KEY_LEN];
	uint8		Ui_prev[SCRAM_KEY_LEN];
	scram_HMAC_ctx hmac_ctx;

	/*
	 * Iterate hash calculation of HMAC entry using given salt.  This is
	 * essentially PBKDF2 (see RFC2898) with HMAC() as the pseudorandom
	 * function.
	 */

	/* First iteration */
	scram_HMAC_init(&hmac_ctx, (uint8 *) password, password_len);
	scram_HMAC_update(&hmac_ctx, salt, saltlen);
	scram_HMAC_update(&hmac_ctx, (char *) &one, sizeof(uint32));
	scram_HMAC_final(Ui_prev, &hmac_ctx);
	memcpy(result, Ui_prev, SCRAM_KEY_LEN);

	/* Subsequent iterations */
	for (i = 2; i <= iterations; i++)
	{
		scram_HMAC_init(&hmac_ctx, (uint8 *) password, password_len);
		scram_HMAC_update(&hmac_ctx, (const char *) Ui_prev, SCRAM_KEY_LEN);
		scram_HMAC_final(Ui, &hmac_ctx);
		for (j = 0; j < SCRAM_KEY_LEN; j++)
			result[j] ^= Ui[j];
		memcpy(Ui_prev, Ui, SCRAM_KEY_LEN);
	}
}