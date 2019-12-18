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
struct request_key_auth {struct key* dest_keyring; } ;
struct key {int /*<<< orphan*/  sem; int /*<<< orphan*/  flags; } ;
struct cred {int jit_keyring; struct key* session_keyring; struct key* process_keyring; struct key* thread_keyring; struct key* request_key_auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  KEY_FLAG_REVOKED ; 
 int /*<<< orphan*/  KEY_NEED_WRITE ; 
#define  KEY_REQKEY_DEFL_DEFAULT 135 
#define  KEY_REQKEY_DEFL_GROUP_KEYRING 134 
#define  KEY_REQKEY_DEFL_PROCESS_KEYRING 133 
#define  KEY_REQKEY_DEFL_REQUESTOR_KEYRING 132 
#define  KEY_REQKEY_DEFL_SESSION_KEYRING 131 
#define  KEY_REQKEY_DEFL_THREAD_KEYRING 130 
#define  KEY_REQKEY_DEFL_USER_KEYRING 129 
#define  KEY_REQKEY_DEFL_USER_SESSION_KEYRING 128 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct request_key_auth* get_request_key_auth (struct key*) ; 
 int /*<<< orphan*/  kenter (char*,struct key*) ; 
 struct key* key_get (struct key*) ; 
 int key_permission (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int /*<<< orphan*/  kleave (char*,int /*<<< orphan*/ ) ; 
 int look_up_user_keyrings (struct key**,struct key**) ; 
 int /*<<< orphan*/  make_key_ref (struct key*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int construct_get_dest_keyring(struct key **_dest_keyring)
{
	struct request_key_auth *rka;
	const struct cred *cred = current_cred();
	struct key *dest_keyring = *_dest_keyring, *authkey;
	int ret;

	kenter("%p", dest_keyring);

	/* find the appropriate keyring */
	if (dest_keyring) {
		/* the caller supplied one */
		key_get(dest_keyring);
	} else {
		bool do_perm_check = true;

		/* use a default keyring; falling through the cases until we
		 * find one that we actually have */
		switch (cred->jit_keyring) {
		case KEY_REQKEY_DEFL_DEFAULT:
		case KEY_REQKEY_DEFL_REQUESTOR_KEYRING:
			if (cred->request_key_auth) {
				authkey = cred->request_key_auth;
				down_read(&authkey->sem);
				rka = get_request_key_auth(authkey);
				if (!test_bit(KEY_FLAG_REVOKED,
					      &authkey->flags))
					dest_keyring =
						key_get(rka->dest_keyring);
				up_read(&authkey->sem);
				if (dest_keyring) {
					do_perm_check = false;
					break;
				}
			}

			/* fall through */
		case KEY_REQKEY_DEFL_THREAD_KEYRING:
			dest_keyring = key_get(cred->thread_keyring);
			if (dest_keyring)
				break;

			/* fall through */
		case KEY_REQKEY_DEFL_PROCESS_KEYRING:
			dest_keyring = key_get(cred->process_keyring);
			if (dest_keyring)
				break;

			/* fall through */
		case KEY_REQKEY_DEFL_SESSION_KEYRING:
			dest_keyring = key_get(cred->session_keyring);

			if (dest_keyring)
				break;

			/* fall through */
		case KEY_REQKEY_DEFL_USER_SESSION_KEYRING:
			ret = look_up_user_keyrings(NULL, &dest_keyring);
			if (ret < 0)
				return ret;
			break;

		case KEY_REQKEY_DEFL_USER_KEYRING:
			ret = look_up_user_keyrings(&dest_keyring, NULL);
			if (ret < 0)
				return ret;
			break;

		case KEY_REQKEY_DEFL_GROUP_KEYRING:
		default:
			BUG();
		}

		/*
		 * Require Write permission on the keyring.  This is essential
		 * because the default keyring may be the session keyring, and
		 * joining a keyring only requires Search permission.
		 *
		 * However, this check is skipped for the "requestor keyring" so
		 * that /sbin/request-key can itself use request_key() to add
		 * keys to the original requestor's destination keyring.
		 */
		if (dest_keyring && do_perm_check) {
			ret = key_permission(make_key_ref(dest_keyring, 1),
					     KEY_NEED_WRITE);
			if (ret) {
				key_put(dest_keyring);
				return ret;
			}
		}
	}

	*_dest_keyring = dest_keyring;
	kleave(" [dk %d]", key_serial(dest_keyring));
	return 0;
}