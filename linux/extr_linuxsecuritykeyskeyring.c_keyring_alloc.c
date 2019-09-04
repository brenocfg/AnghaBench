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
struct key_restriction {int dummy; } ;
struct key {int dummy; } ;
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
typedef  int /*<<< orphan*/  key_perm_t ;

/* Variables and functions */
 struct key* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (struct key*) ; 
 struct key* key_alloc (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred const*,int /*<<< orphan*/ ,unsigned long,struct key_restriction*) ; 
 int key_instantiate_and_link (struct key*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_type_keyring ; 

struct key *keyring_alloc(const char *description, kuid_t uid, kgid_t gid,
			  const struct cred *cred, key_perm_t perm,
			  unsigned long flags,
			  struct key_restriction *restrict_link,
			  struct key *dest)
{
	struct key *keyring;
	int ret;

	keyring = key_alloc(&key_type_keyring, description,
			    uid, gid, cred, perm, flags, restrict_link);
	if (!IS_ERR(keyring)) {
		ret = key_instantiate_and_link(keyring, NULL, 0, dest, NULL);
		if (ret < 0) {
			key_put(keyring);
			keyring = ERR_PTR(ret);
		}
	}

	return keyring;
}