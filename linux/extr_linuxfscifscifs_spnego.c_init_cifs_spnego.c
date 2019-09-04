#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct key {int /*<<< orphan*/  flags; } ;
struct cred {int /*<<< orphan*/  jit_keyring; struct key* thread_keyring; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_ALLOC_NOT_IN_QUOTA ; 
 int /*<<< orphan*/  KEY_FLAG_ROOT_CAN_CLEAR ; 
 int KEY_POS_ALL ; 
 int KEY_POS_SETATTR ; 
 int /*<<< orphan*/  KEY_REQKEY_DEFL_THREAD_KEYRING ; 
 int KEY_USR_READ ; 
 int KEY_USR_VIEW ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ cifs_spnego_key_type ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 struct key* keyring_alloc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct cred* prepare_kernel_cred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_cred (struct cred*) ; 
 int register_key_type (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cred* spnego_cred ; 

int
init_cifs_spnego(void)
{
	struct cred *cred;
	struct key *keyring;
	int ret;

	cifs_dbg(FYI, "Registering the %s key type\n",
		 cifs_spnego_key_type.name);

	/*
	 * Create an override credential set with special thread keyring for
	 * spnego upcalls.
	 */

	cred = prepare_kernel_cred(NULL);
	if (!cred)
		return -ENOMEM;

	keyring = keyring_alloc(".cifs_spnego",
				GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, cred,
				(KEY_POS_ALL & ~KEY_POS_SETATTR) |
				KEY_USR_VIEW | KEY_USR_READ,
				KEY_ALLOC_NOT_IN_QUOTA, NULL, NULL);
	if (IS_ERR(keyring)) {
		ret = PTR_ERR(keyring);
		goto failed_put_cred;
	}

	ret = register_key_type(&cifs_spnego_key_type);
	if (ret < 0)
		goto failed_put_key;

	/*
	 * instruct request_key() to use this special keyring as a cache for
	 * the results it looks up
	 */
	set_bit(KEY_FLAG_ROOT_CAN_CLEAR, &keyring->flags);
	cred->thread_keyring = keyring;
	cred->jit_keyring = KEY_REQKEY_DEFL_THREAD_KEYRING;
	spnego_cred = cred;

	cifs_dbg(FYI, "cifs spnego keyring: %d\n", key_serial(keyring));
	return 0;

failed_put_key:
	key_put(keyring);
failed_put_cred:
	put_cred(cred);
	return ret;
}