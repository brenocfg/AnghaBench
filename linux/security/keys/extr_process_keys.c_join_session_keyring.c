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
struct key {long serial; } ;
struct cred {struct key* session_keyring; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 long ENOKEY ; 
 long ENOMEM ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_ALLOC_IN_QUOTA ; 
 int KEY_POS_ALL ; 
 int KEY_USR_LINK ; 
 int KEY_USR_READ ; 
 int KEY_USR_VIEW ; 
 long PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  abort_creds (struct cred*) ; 
 long commit_creds (struct cred*) ; 
 struct cred* current_cred () ; 
 struct key* find_keyring_by_name (char const*,int) ; 
 long install_session_keyring_to_cred (struct cred*,struct key*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_session_mutex ; 
 struct key* keyring_alloc (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cred* prepare_creds () ; 

long join_session_keyring(const char *name)
{
	const struct cred *old;
	struct cred *new;
	struct key *keyring;
	long ret, serial;

	new = prepare_creds();
	if (!new)
		return -ENOMEM;
	old = current_cred();

	/* if no name is provided, install an anonymous keyring */
	if (!name) {
		ret = install_session_keyring_to_cred(new, NULL);
		if (ret < 0)
			goto error;

		serial = new->session_keyring->serial;
		ret = commit_creds(new);
		if (ret == 0)
			ret = serial;
		goto okay;
	}

	/* allow the user to join or create a named keyring */
	mutex_lock(&key_session_mutex);

	/* look for an existing keyring of this name */
	keyring = find_keyring_by_name(name, false);
	if (PTR_ERR(keyring) == -ENOKEY) {
		/* not found - try and create a new one */
		keyring = keyring_alloc(
			name, old->uid, old->gid, old,
			KEY_POS_ALL | KEY_USR_VIEW | KEY_USR_READ | KEY_USR_LINK,
			KEY_ALLOC_IN_QUOTA, NULL, NULL);
		if (IS_ERR(keyring)) {
			ret = PTR_ERR(keyring);
			goto error2;
		}
	} else if (IS_ERR(keyring)) {
		ret = PTR_ERR(keyring);
		goto error2;
	} else if (keyring == new->session_keyring) {
		ret = 0;
		goto error3;
	}

	/* we've got a keyring - now to install it */
	ret = install_session_keyring_to_cred(new, keyring);
	if (ret < 0)
		goto error3;

	commit_creds(new);
	mutex_unlock(&key_session_mutex);

	ret = keyring->serial;
	key_put(keyring);
okay:
	return ret;

error3:
	key_put(keyring);
error2:
	mutex_unlock(&key_session_mutex);
error:
	abort_creds(new);
	return ret;
}