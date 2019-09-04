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
 int /*<<< orphan*/  KEY_FLAG_ROOT_CAN_INVAL ; 
 int /*<<< orphan*/  KEY_NEED_SEARCH ; 
 long PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_invalidate (struct key*) ; 
 int /*<<< orphan*/  key_ref_put (int /*<<< orphan*/ ) ; 
 struct key* key_ref_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kleave (char*,long) ; 
 int /*<<< orphan*/  lookup_user_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

long keyctl_invalidate_key(key_serial_t id)
{
	key_ref_t key_ref;
	struct key *key;
	long ret;

	kenter("%d", id);

	key_ref = lookup_user_key(id, 0, KEY_NEED_SEARCH);
	if (IS_ERR(key_ref)) {
		ret = PTR_ERR(key_ref);

		/* Root is permitted to invalidate certain special keys */
		if (capable(CAP_SYS_ADMIN)) {
			key_ref = lookup_user_key(id, 0, 0);
			if (IS_ERR(key_ref))
				goto error;
			if (test_bit(KEY_FLAG_ROOT_CAN_INVAL,
				     &key_ref_to_ptr(key_ref)->flags))
				goto invalidate;
			goto error_put;
		}

		goto error;
	}

invalidate:
	key = key_ref_to_ptr(key_ref);
	ret = 0;
	if (test_bit(KEY_FLAG_KEEP, &key->flags))
		ret = -EPERM;
	else
		key_invalidate(key);
error_put:
	key_ref_put(key_ref);
error:
	kleave(" = %ld", ret);
	return ret;
}