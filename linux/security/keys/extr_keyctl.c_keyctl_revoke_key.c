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
 long EACCES ; 
 long EPERM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_FLAG_KEEP ; 
 int /*<<< orphan*/  KEY_NEED_SETATTR ; 
 int /*<<< orphan*/  KEY_NEED_WRITE ; 
 long PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_ref_put (int /*<<< orphan*/ ) ; 
 struct key* key_ref_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_revoke (struct key*) ; 
 int /*<<< orphan*/  lookup_user_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

long keyctl_revoke_key(key_serial_t id)
{
	key_ref_t key_ref;
	struct key *key;
	long ret;

	key_ref = lookup_user_key(id, 0, KEY_NEED_WRITE);
	if (IS_ERR(key_ref)) {
		ret = PTR_ERR(key_ref);
		if (ret != -EACCES)
			goto error;
		key_ref = lookup_user_key(id, 0, KEY_NEED_SETATTR);
		if (IS_ERR(key_ref)) {
			ret = PTR_ERR(key_ref);
			goto error;
		}
	}

	key = key_ref_to_ptr(key_ref);
	ret = 0;
	if (test_bit(KEY_FLAG_KEEP, &key->flags))
		ret = -EPERM;
	else
		key_revoke(key);

	key_ref_put(key_ref);
error:
	return ret;
}