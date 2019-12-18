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
struct cred {int jit_keyring; } ;

/* Variables and functions */
 int EINVAL ; 
 long ENOMEM ; 
#define  KEY_REQKEY_DEFL_DEFAULT 136 
#define  KEY_REQKEY_DEFL_GROUP_KEYRING 135 
#define  KEY_REQKEY_DEFL_NO_CHANGE 134 
#define  KEY_REQKEY_DEFL_PROCESS_KEYRING 133 
#define  KEY_REQKEY_DEFL_REQUESTOR_KEYRING 132 
#define  KEY_REQKEY_DEFL_SESSION_KEYRING 131 
#define  KEY_REQKEY_DEFL_THREAD_KEYRING 130 
#define  KEY_REQKEY_DEFL_USER_KEYRING 129 
#define  KEY_REQKEY_DEFL_USER_SESSION_KEYRING 128 
 int /*<<< orphan*/  abort_creds (struct cred*) ; 
 int /*<<< orphan*/  commit_creds (struct cred*) ; 
 int current_cred_xxx (int /*<<< orphan*/ ) ; 
 int install_process_keyring_to_cred (struct cred*) ; 
 int install_thread_keyring_to_cred (struct cred*) ; 
 int /*<<< orphan*/  jit_keyring ; 
 struct cred* prepare_creds () ; 

long keyctl_set_reqkey_keyring(int reqkey_defl)
{
	struct cred *new;
	int ret, old_setting;

	old_setting = current_cred_xxx(jit_keyring);

	if (reqkey_defl == KEY_REQKEY_DEFL_NO_CHANGE)
		return old_setting;

	new = prepare_creds();
	if (!new)
		return -ENOMEM;

	switch (reqkey_defl) {
	case KEY_REQKEY_DEFL_THREAD_KEYRING:
		ret = install_thread_keyring_to_cred(new);
		if (ret < 0)
			goto error;
		goto set;

	case KEY_REQKEY_DEFL_PROCESS_KEYRING:
		ret = install_process_keyring_to_cred(new);
		if (ret < 0)
			goto error;
		goto set;

	case KEY_REQKEY_DEFL_DEFAULT:
	case KEY_REQKEY_DEFL_SESSION_KEYRING:
	case KEY_REQKEY_DEFL_USER_KEYRING:
	case KEY_REQKEY_DEFL_USER_SESSION_KEYRING:
	case KEY_REQKEY_DEFL_REQUESTOR_KEYRING:
		goto set;

	case KEY_REQKEY_DEFL_NO_CHANGE:
	case KEY_REQKEY_DEFL_GROUP_KEYRING:
	default:
		ret = -EINVAL;
		goto error;
	}

set:
	new->jit_keyring = reqkey_defl;
	commit_creds(new);
	return old_setting;
error:
	abort_creds(new);
	return ret;
}