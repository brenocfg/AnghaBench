#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  hash_algo; int /*<<< orphan*/  session_key_encryption_key_bytes; scalar_t__ signature; } ;
struct TYPE_6__ {TYPE_2__ password; } ;
struct TYPE_4__ {scalar_t__ encrypted_key_size; scalar_t__* encrypted_key; } ;
struct ecryptfs_auth_tok {int version; TYPE_3__ token; TYPE_1__ session_key; int /*<<< orphan*/  token_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECRYPTFS_MAX_KEY_BYTES ; 
 int /*<<< orphan*/  ECRYPTFS_PASSWORD ; 
 int /*<<< orphan*/  ECRYPTFS_PASSWORD_SIG_SIZE ; 
 int /*<<< orphan*/  ECRYPTFS_PERSISTENT_PASSWORD ; 
 int /*<<< orphan*/  ECRYPTFS_SESSION_KEY_ENCRYPTION_KEY_SET ; 
 int /*<<< orphan*/  PGP_DIGEST_ALGO_SHA512 ; 
 int /*<<< orphan*/  ecryptfs_get_versions (int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int /*<<< orphan*/ ) ; 

int ecryptfs_fill_auth_tok(struct ecryptfs_auth_tok *auth_tok,
			   const char *key_desc)
{
	int major, minor;

	ecryptfs_get_versions(&major, &minor, NULL);
	auth_tok->version = (((uint16_t)(major << 8) & 0xFF00)
			     | ((uint16_t)minor & 0x00FF));
	auth_tok->token_type = ECRYPTFS_PASSWORD;
	strncpy((char *)auth_tok->token.password.signature, key_desc,
		ECRYPTFS_PASSWORD_SIG_SIZE);
	auth_tok->token.password.session_key_encryption_key_bytes =
		ECRYPTFS_MAX_KEY_BYTES;
	/*
	 * Removed auth_tok->token.password.salt and
	 * auth_tok->token.password.session_key_encryption_key
	 * initialization from the original code
	 */
	/* TODO: Make the hash parameterizable via policy */
	auth_tok->token.password.flags |=
		ECRYPTFS_SESSION_KEY_ENCRYPTION_KEY_SET;
	/* The kernel code will encrypt the session key. */
	auth_tok->session_key.encrypted_key[0] = 0;
	auth_tok->session_key.encrypted_key_size = 0;
	/* Default; subject to change by kernel eCryptfs */
	auth_tok->token.password.hash_algo = PGP_DIGEST_ALGO_SHA512;
	auth_tok->token.password.flags &= ~(ECRYPTFS_PERSISTENT_PASSWORD);
	return 0;
}