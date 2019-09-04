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
typedef  int uid_t ;
struct user_struct {struct key* session_keyring; struct key* uid_keyring; int /*<<< orphan*/  uid; } ;
struct key {int dummy; } ;
struct cred {int /*<<< orphan*/  user_ns; struct user_struct* user; } ;
typedef  int key_perm_t ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_GID ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int KEY_ALLOC_IN_QUOTA ; 
 int KEY_ALLOC_UID_KEYRING ; 
 int KEY_POS_ALL ; 
 int KEY_POS_SETATTR ; 
 int KEY_USR_ALL ; 
 int PTR_ERR (struct key*) ; 
 struct cred* current_cred () ; 
 struct key* find_keyring_by_name (char*,int) ; 
 int from_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kenter (char*,struct user_struct*,int) ; 
 int key_link (struct key*,struct key*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_user_keyring_mutex ; 
 struct key* keyring_alloc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kleave (char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int install_user_keyrings(void)
{
	struct user_struct *user;
	const struct cred *cred;
	struct key *uid_keyring, *session_keyring;
	key_perm_t user_keyring_perm;
	char buf[20];
	int ret;
	uid_t uid;

	user_keyring_perm = (KEY_POS_ALL & ~KEY_POS_SETATTR) | KEY_USR_ALL;
	cred = current_cred();
	user = cred->user;
	uid = from_kuid(cred->user_ns, user->uid);

	kenter("%p{%u}", user, uid);

	if (user->uid_keyring && user->session_keyring) {
		kleave(" = 0 [exist]");
		return 0;
	}

	mutex_lock(&key_user_keyring_mutex);
	ret = 0;

	if (!user->uid_keyring) {
		/* get the UID-specific keyring
		 * - there may be one in existence already as it may have been
		 *   pinned by a session, but the user_struct pointing to it
		 *   may have been destroyed by setuid */
		sprintf(buf, "_uid.%u", uid);

		uid_keyring = find_keyring_by_name(buf, true);
		if (IS_ERR(uid_keyring)) {
			uid_keyring = keyring_alloc(buf, user->uid, INVALID_GID,
						    cred, user_keyring_perm,
						    KEY_ALLOC_UID_KEYRING |
							KEY_ALLOC_IN_QUOTA,
						    NULL, NULL);
			if (IS_ERR(uid_keyring)) {
				ret = PTR_ERR(uid_keyring);
				goto error;
			}
		}

		/* get a default session keyring (which might also exist
		 * already) */
		sprintf(buf, "_uid_ses.%u", uid);

		session_keyring = find_keyring_by_name(buf, true);
		if (IS_ERR(session_keyring)) {
			session_keyring =
				keyring_alloc(buf, user->uid, INVALID_GID,
					      cred, user_keyring_perm,
					      KEY_ALLOC_UID_KEYRING |
						  KEY_ALLOC_IN_QUOTA,
					      NULL, NULL);
			if (IS_ERR(session_keyring)) {
				ret = PTR_ERR(session_keyring);
				goto error_release;
			}

			/* we install a link from the user session keyring to
			 * the user keyring */
			ret = key_link(session_keyring, uid_keyring);
			if (ret < 0)
				goto error_release_both;
		}

		/* install the keyrings */
		user->uid_keyring = uid_keyring;
		user->session_keyring = session_keyring;
	}

	mutex_unlock(&key_user_keyring_mutex);
	kleave(" = 0");
	return 0;

error_release_both:
	key_put(session_keyring);
error_release:
	key_put(uid_keyring);
error:
	mutex_unlock(&key_user_keyring_mutex);
	kleave(" = %d", ret);
	return ret;
}