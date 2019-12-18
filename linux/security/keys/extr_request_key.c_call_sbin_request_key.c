#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_key_auth {scalar_t__ op; struct key* target_key; } ;
struct key {int serial; int /*<<< orphan*/  flags; } ;
struct cred {struct key* session_keyring; TYPE_2__* process_keyring; TYPE_1__* thread_keyring; int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; } ;
typedef  int key_serial_t ;
struct TYPE_4__ {int serial; } ;
struct TYPE_3__ {int serial; } ;

/* Variables and functions */
 int ENOKEY ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_ALLOC_QUOTA_OVERRUN ; 
 int /*<<< orphan*/  KEY_FLAG_USER_CONSTRUCT ; 
 int KEY_POS_ALL ; 
 int KEY_USR_READ ; 
 int KEY_USR_VIEW ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  UMH_WAIT_PROC ; 
 int call_usermodehelper_keys (char const*,char**,char**,struct key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_request_key (struct key*,int) ; 
 struct cred* current_cred () ; 
 int from_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cred* get_current_cred () ; 
 struct request_key_auth* get_request_key_auth (struct key*) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  kdebug (char*,int) ; 
 int /*<<< orphan*/  kenter (char*,int,int,scalar_t__) ; 
 int key_link (struct key*,struct key*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 scalar_t__ key_validate (struct key*) ; 
 struct key* keyring_alloc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kleave (char*,int) ; 
 int look_up_user_keyrings (int /*<<< orphan*/ *,struct key**) ; 
 int /*<<< orphan*/  put_cred (struct cred const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int call_sbin_request_key(struct key *authkey, void *aux)
{
	static char const request_key[] = "/sbin/request-key";
	struct request_key_auth *rka = get_request_key_auth(authkey);
	const struct cred *cred = current_cred();
	key_serial_t prkey, sskey;
	struct key *key = rka->target_key, *keyring, *session, *user_session;
	char *argv[9], *envp[3], uid_str[12], gid_str[12];
	char key_str[12], keyring_str[3][12];
	char desc[20];
	int ret, i;

	kenter("{%d},{%d},%s", key->serial, authkey->serial, rka->op);

	ret = look_up_user_keyrings(NULL, &user_session);
	if (ret < 0)
		goto error_us;

	/* allocate a new session keyring */
	sprintf(desc, "_req.%u", key->serial);

	cred = get_current_cred();
	keyring = keyring_alloc(desc, cred->fsuid, cred->fsgid, cred,
				KEY_POS_ALL | KEY_USR_VIEW | KEY_USR_READ,
				KEY_ALLOC_QUOTA_OVERRUN, NULL, NULL);
	put_cred(cred);
	if (IS_ERR(keyring)) {
		ret = PTR_ERR(keyring);
		goto error_alloc;
	}

	/* attach the auth key to the session keyring */
	ret = key_link(keyring, authkey);
	if (ret < 0)
		goto error_link;

	/* record the UID and GID */
	sprintf(uid_str, "%d", from_kuid(&init_user_ns, cred->fsuid));
	sprintf(gid_str, "%d", from_kgid(&init_user_ns, cred->fsgid));

	/* we say which key is under construction */
	sprintf(key_str, "%d", key->serial);

	/* we specify the process's default keyrings */
	sprintf(keyring_str[0], "%d",
		cred->thread_keyring ? cred->thread_keyring->serial : 0);

	prkey = 0;
	if (cred->process_keyring)
		prkey = cred->process_keyring->serial;
	sprintf(keyring_str[1], "%d", prkey);

	session = cred->session_keyring;
	if (!session)
		session = user_session;
	sskey = session->serial;

	sprintf(keyring_str[2], "%d", sskey);

	/* set up a minimal environment */
	i = 0;
	envp[i++] = "HOME=/";
	envp[i++] = "PATH=/sbin:/bin:/usr/sbin:/usr/bin";
	envp[i] = NULL;

	/* set up the argument list */
	i = 0;
	argv[i++] = (char *)request_key;
	argv[i++] = (char *)rka->op;
	argv[i++] = key_str;
	argv[i++] = uid_str;
	argv[i++] = gid_str;
	argv[i++] = keyring_str[0];
	argv[i++] = keyring_str[1];
	argv[i++] = keyring_str[2];
	argv[i] = NULL;

	/* do it */
	ret = call_usermodehelper_keys(request_key, argv, envp, keyring,
				       UMH_WAIT_PROC);
	kdebug("usermode -> 0x%x", ret);
	if (ret >= 0) {
		/* ret is the exit/wait code */
		if (test_bit(KEY_FLAG_USER_CONSTRUCT, &key->flags) ||
		    key_validate(key) < 0)
			ret = -ENOKEY;
		else
			/* ignore any errors from userspace if the key was
			 * instantiated */
			ret = 0;
	}

error_link:
	key_put(keyring);

error_alloc:
	key_put(user_session);
error_us:
	complete_request_key(authkey, ret);
	kleave(" = %d", ret);
	return ret;
}