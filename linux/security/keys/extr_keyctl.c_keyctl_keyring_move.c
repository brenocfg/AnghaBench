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
typedef  int /*<<< orphan*/  key_serial_t ;
typedef  int /*<<< orphan*/  key_ref_t ;

/* Variables and functions */
 long EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 unsigned int KEYCTL_MOVE_EXCL ; 
 int /*<<< orphan*/  KEY_LOOKUP_CREATE ; 
 int /*<<< orphan*/  KEY_NEED_LINK ; 
 int /*<<< orphan*/  KEY_NEED_WRITE ; 
 long PTR_ERR (int /*<<< orphan*/ ) ; 
 long key_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  key_ref_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_ref_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_user_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

long keyctl_keyring_move(key_serial_t id, key_serial_t from_ringid,
			 key_serial_t to_ringid, unsigned int flags)
{
	key_ref_t key_ref, from_ref, to_ref;
	long ret;

	if (flags & ~KEYCTL_MOVE_EXCL)
		return -EINVAL;

	key_ref = lookup_user_key(id, KEY_LOOKUP_CREATE, KEY_NEED_LINK);
	if (IS_ERR(key_ref))
		return PTR_ERR(key_ref);

	from_ref = lookup_user_key(from_ringid, 0, KEY_NEED_WRITE);
	if (IS_ERR(from_ref)) {
		ret = PTR_ERR(from_ref);
		goto error2;
	}

	to_ref = lookup_user_key(to_ringid, KEY_LOOKUP_CREATE, KEY_NEED_WRITE);
	if (IS_ERR(to_ref)) {
		ret = PTR_ERR(to_ref);
		goto error3;
	}

	ret = key_move(key_ref_to_ptr(key_ref), key_ref_to_ptr(from_ref),
		       key_ref_to_ptr(to_ref), flags);

	key_ref_put(to_ref);
error3:
	key_ref_put(from_ref);
error2:
	key_ref_put(key_ref);
	return ret;
}