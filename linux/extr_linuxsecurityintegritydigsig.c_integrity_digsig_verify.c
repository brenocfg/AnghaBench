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

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 unsigned int const INTEGRITY_KEYRING_MAX ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int asymmetric_verify (int /*<<< orphan*/ *,char const*,int,char const*,int) ; 
 int digsig_verify (int /*<<< orphan*/ *,char const*,int,char const*,int) ; 
 int /*<<< orphan*/  key_type_keyring ; 
 int /*<<< orphan*/ ** keyring ; 
 int /*<<< orphan*/ * keyring_name ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * request_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int integrity_digsig_verify(const unsigned int id, const char *sig, int siglen,
			    const char *digest, int digestlen)
{
	if (id >= INTEGRITY_KEYRING_MAX || siglen < 2)
		return -EINVAL;

	if (!keyring[id]) {
		keyring[id] =
			request_key(&key_type_keyring, keyring_name[id], NULL);
		if (IS_ERR(keyring[id])) {
			int err = PTR_ERR(keyring[id]);
			pr_err("no %s keyring: %d\n", keyring_name[id], err);
			keyring[id] = NULL;
			return err;
		}
	}

	switch (sig[1]) {
	case 1:
		/* v1 API expect signature without xattr type */
		return digsig_verify(keyring[id], sig + 1, siglen - 1,
				     digest, digestlen);
	case 2:
		return asymmetric_verify(keyring[id], sig, siglen,
					 digest, digestlen);
	}

	return -EOPNOTSUPP;
}