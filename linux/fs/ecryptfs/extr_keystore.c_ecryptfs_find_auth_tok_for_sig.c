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
struct key {int dummy; } ;
struct ecryptfs_mount_crypt_stat {int flags; } ;
struct ecryptfs_auth_tok {int dummy; } ;

/* Variables and functions */
 int ECRYPTFS_GLOBAL_MOUNT_AUTH_TOK_ONLY ; 
 int EINVAL ; 
 int ENOENT ; 
 int ecryptfs_find_global_auth_tok_for_sig (struct key**,struct ecryptfs_auth_tok**,struct ecryptfs_mount_crypt_stat*,char*) ; 
 int ecryptfs_keyring_auth_tok_for_sig (struct key**,struct ecryptfs_auth_tok**,char*) ; 

__attribute__((used)) static int
ecryptfs_find_auth_tok_for_sig(
	struct key **auth_tok_key,
	struct ecryptfs_auth_tok **auth_tok,
	struct ecryptfs_mount_crypt_stat *mount_crypt_stat,
	char *sig)
{
	int rc = 0;

	rc = ecryptfs_find_global_auth_tok_for_sig(auth_tok_key, auth_tok,
						   mount_crypt_stat, sig);
	if (rc == -ENOENT) {
		/* if the flag ECRYPTFS_GLOBAL_MOUNT_AUTH_TOK_ONLY is set in the
		 * mount_crypt_stat structure, we prevent to use auth toks that
		 * are not inserted through the ecryptfs_add_global_auth_tok
		 * function.
		 */
		if (mount_crypt_stat->flags
				& ECRYPTFS_GLOBAL_MOUNT_AUTH_TOK_ONLY)
			return -EINVAL;

		rc = ecryptfs_keyring_auth_tok_for_sig(auth_tok_key, auth_tok,
						       sig);
	}
	return rc;
}