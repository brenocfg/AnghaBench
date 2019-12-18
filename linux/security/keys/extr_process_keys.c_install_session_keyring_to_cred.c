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
struct cred {struct key* session_keyring; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct key*) ; 
 unsigned long KEY_ALLOC_IN_QUOTA ; 
 unsigned long KEY_ALLOC_QUOTA_OVERRUN ; 
 int KEY_POS_ALL ; 
 int KEY_USR_READ ; 
 int KEY_USR_VIEW ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  __key_get (struct key*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 struct key* keyring_alloc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred*,int,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 

int install_session_keyring_to_cred(struct cred *cred, struct key *keyring)
{
	unsigned long flags;
	struct key *old;

	might_sleep();

	/* create an empty session keyring */
	if (!keyring) {
		flags = KEY_ALLOC_QUOTA_OVERRUN;
		if (cred->session_keyring)
			flags = KEY_ALLOC_IN_QUOTA;

		keyring = keyring_alloc("_ses", cred->uid, cred->gid, cred,
					KEY_POS_ALL | KEY_USR_VIEW | KEY_USR_READ,
					flags, NULL, NULL);
		if (IS_ERR(keyring))
			return PTR_ERR(keyring);
	} else {
		__key_get(keyring);
	}

	/* install the keyring */
	old = cred->session_keyring;
	cred->session_keyring = keyring;

	if (old)
		key_put(old);

	return 0;
}