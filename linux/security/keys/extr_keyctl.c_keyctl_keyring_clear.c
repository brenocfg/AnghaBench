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
struct key {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  key_serial_t ;
typedef  int /*<<< orphan*/  key_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 long EPERM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_FLAG_KEEP ; 
 int /*<<< orphan*/  KEY_FLAG_ROOT_CAN_CLEAR ; 
 int /*<<< orphan*/  KEY_LOOKUP_CREATE ; 
 int /*<<< orphan*/  KEY_NEED_WRITE ; 
 long PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_ref_put (int /*<<< orphan*/ ) ; 
 struct key* key_ref_to_ptr (int /*<<< orphan*/ ) ; 
 long keyring_clear (struct key*) ; 
 int /*<<< orphan*/  lookup_user_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

long keyctl_keyring_clear(key_serial_t ringid)
{
	key_ref_t keyring_ref;
	struct key *keyring;
	long ret;

	keyring_ref = lookup_user_key(ringid, KEY_LOOKUP_CREATE, KEY_NEED_WRITE);
	if (IS_ERR(keyring_ref)) {
		ret = PTR_ERR(keyring_ref);

		/* Root is permitted to invalidate certain special keyrings */
		if (capable(CAP_SYS_ADMIN)) {
			keyring_ref = lookup_user_key(ringid, 0, 0);
			if (IS_ERR(keyring_ref))
				goto error;
			if (test_bit(KEY_FLAG_ROOT_CAN_CLEAR,
				     &key_ref_to_ptr(keyring_ref)->flags))
				goto clear;
			goto error_put;
		}

		goto error;
	}

clear:
	keyring = key_ref_to_ptr(keyring_ref);
	if (test_bit(KEY_FLAG_KEEP, &keyring->flags))
		ret = -EPERM;
	else
		ret = keyring_clear(keyring);
error_put:
	key_ref_put(keyring_ref);
error:
	return ret;
}