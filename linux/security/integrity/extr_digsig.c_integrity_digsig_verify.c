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

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 int asymmetric_verify (struct key*,char const*,int,char const*,int) ; 
 int digsig_verify (struct key*,char const*,int,char const*,int) ; 
 struct key* integrity_keyring_from_id (unsigned int const) ; 

int integrity_digsig_verify(const unsigned int id, const char *sig, int siglen,
			    const char *digest, int digestlen)
{
	struct key *keyring;

	if (siglen < 2)
		return -EINVAL;

	keyring = integrity_keyring_from_id(id);
	if (IS_ERR(keyring))
		return PTR_ERR(keyring);

	switch (sig[1]) {
	case 1:
		/* v1 API expect signature without xattr type */
		return digsig_verify(keyring, sig + 1, siglen - 1, digest,
				     digestlen);
	case 2:
		return asymmetric_verify(keyring, sig, siglen, digest,
					 digestlen);
	}

	return -EOPNOTSUPP;
}