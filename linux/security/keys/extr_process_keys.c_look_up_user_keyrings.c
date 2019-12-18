#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uid_t ;
struct user_namespace {int /*<<< orphan*/  keyring_sem; } ;
struct key {int dummy; } ;
struct cred {TYPE_1__* user; } ;
typedef  struct key* key_ref_t ;
typedef  int key_perm_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 struct key* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVALID_GID ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int KEY_ALLOC_IN_QUOTA ; 
 int KEY_ALLOC_UID_KEYRING ; 
 int KEY_POS_ALL ; 
 int KEY_POS_SETATTR ; 
 int KEY_USR_ALL ; 
 int PTR_ERR (struct key*) ; 
 struct cred* current_cred () ; 
 struct user_namespace* current_user_ns () ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int from_kuid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 struct key* get_user_register (struct user_namespace*) ; 
 int /*<<< orphan*/  kdebug (char*,struct key*) ; 
 int /*<<< orphan*/  kenter (char*,int) ; 
 int key_link (struct key*,struct key*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 struct key* key_ref_to_ptr (struct key*) ; 
 int /*<<< orphan*/  key_type_keyring ; 
 struct key* keyring_alloc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred const*,int,int,int /*<<< orphan*/ *,struct key*) ; 
 struct key* keyring_search (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kleave (char*,...) ; 
 int /*<<< orphan*/  make_key_ref (struct key*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int look_up_user_keyrings(struct key **_user_keyring,
			  struct key **_user_session_keyring)
{
	const struct cred *cred = current_cred();
	struct user_namespace *user_ns = current_user_ns();
	struct key *reg_keyring, *uid_keyring, *session_keyring;
	key_perm_t user_keyring_perm;
	key_ref_t uid_keyring_r, session_keyring_r;
	uid_t uid = from_kuid(user_ns, cred->user->uid);
	char buf[20];
	int ret;

	user_keyring_perm = (KEY_POS_ALL & ~KEY_POS_SETATTR) | KEY_USR_ALL;

	kenter("%u", uid);

	reg_keyring = get_user_register(user_ns);
	if (IS_ERR(reg_keyring))
		return PTR_ERR(reg_keyring);

	down_write(&user_ns->keyring_sem);
	ret = 0;

	/* Get the user keyring.  Note that there may be one in existence
	 * already as it may have been pinned by a session, but the user_struct
	 * pointing to it may have been destroyed by setuid.
	 */
	snprintf(buf, sizeof(buf), "_uid.%u", uid);
	uid_keyring_r = keyring_search(make_key_ref(reg_keyring, true),
				       &key_type_keyring, buf, false);
	kdebug("_uid %p", uid_keyring_r);
	if (uid_keyring_r == ERR_PTR(-EAGAIN)) {
		uid_keyring = keyring_alloc(buf, cred->user->uid, INVALID_GID,
					    cred, user_keyring_perm,
					    KEY_ALLOC_UID_KEYRING |
					    KEY_ALLOC_IN_QUOTA,
					    NULL, reg_keyring);
		if (IS_ERR(uid_keyring)) {
			ret = PTR_ERR(uid_keyring);
			goto error;
		}
	} else if (IS_ERR(uid_keyring_r)) {
		ret = PTR_ERR(uid_keyring_r);
		goto error;
	} else {
		uid_keyring = key_ref_to_ptr(uid_keyring_r);
	}

	/* Get a default session keyring (which might also exist already) */
	snprintf(buf, sizeof(buf), "_uid_ses.%u", uid);
	session_keyring_r = keyring_search(make_key_ref(reg_keyring, true),
					   &key_type_keyring, buf, false);
	kdebug("_uid_ses %p", session_keyring_r);
	if (session_keyring_r == ERR_PTR(-EAGAIN)) {
		session_keyring = keyring_alloc(buf, cred->user->uid, INVALID_GID,
						cred, user_keyring_perm,
						KEY_ALLOC_UID_KEYRING |
						KEY_ALLOC_IN_QUOTA,
						NULL, NULL);
		if (IS_ERR(session_keyring)) {
			ret = PTR_ERR(session_keyring);
			goto error_release;
		}

		/* We install a link from the user session keyring to
		 * the user keyring.
		 */
		ret = key_link(session_keyring, uid_keyring);
		if (ret < 0)
			goto error_release_session;

		/* And only then link the user-session keyring to the
		 * register.
		 */
		ret = key_link(reg_keyring, session_keyring);
		if (ret < 0)
			goto error_release_session;
	} else if (IS_ERR(session_keyring_r)) {
		ret = PTR_ERR(session_keyring_r);
		goto error_release;
	} else {
		session_keyring = key_ref_to_ptr(session_keyring_r);
	}

	up_write(&user_ns->keyring_sem);

	if (_user_session_keyring)
		*_user_session_keyring = session_keyring;
	else
		key_put(session_keyring);
	if (_user_keyring)
		*_user_keyring = uid_keyring;
	else
		key_put(uid_keyring);
	kleave(" = 0");
	return 0;

error_release_session:
	key_put(session_keyring);
error_release:
	key_put(uid_keyring);
error:
	up_write(&user_ns->keyring_sem);
	kleave(" = %d", ret);
	return ret;
}