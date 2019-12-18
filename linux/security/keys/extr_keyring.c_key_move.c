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
struct key {int /*<<< orphan*/  index_key; int /*<<< orphan*/  serial; } ;
struct assoc_array_edit {scalar_t__ dead_leaf; } ;

/* Variables and functions */
 int EEXIST ; 
 unsigned int KEYCTL_MOVE_EXCL ; 
 int /*<<< orphan*/  __key_link (struct key*,struct assoc_array_edit**) ; 
 int __key_link_begin (struct key*,int /*<<< orphan*/ *,struct assoc_array_edit**) ; 
 int __key_link_check_live_key (struct key*,struct key*) ; 
 int __key_link_check_restriction (struct key*,struct key*) ; 
 int /*<<< orphan*/  __key_link_end (struct key*,int /*<<< orphan*/ *,struct assoc_array_edit*) ; 
 int __key_move_lock (struct key*,struct key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __key_unlink (struct key*,struct key*,struct assoc_array_edit**) ; 
 int __key_unlink_begin (struct key*,struct key*,struct assoc_array_edit**) ; 
 int /*<<< orphan*/  __key_unlink_end (struct key*,struct key*,struct assoc_array_edit*) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_check (struct key*) ; 
 int /*<<< orphan*/  kleave (char*,int) ; 

int key_move(struct key *key,
	     struct key *from_keyring,
	     struct key *to_keyring,
	     unsigned int flags)
{
	struct assoc_array_edit *from_edit = NULL, *to_edit = NULL;
	int ret;

	kenter("%d,%d,%d", key->serial, from_keyring->serial, to_keyring->serial);

	if (from_keyring == to_keyring)
		return 0;

	key_check(key);
	key_check(from_keyring);
	key_check(to_keyring);

	ret = __key_move_lock(from_keyring, to_keyring, &key->index_key);
	if (ret < 0)
		goto out;
	ret = __key_unlink_begin(from_keyring, key, &from_edit);
	if (ret < 0)
		goto error;
	ret = __key_link_begin(to_keyring, &key->index_key, &to_edit);
	if (ret < 0)
		goto error;

	ret = -EEXIST;
	if (to_edit->dead_leaf && (flags & KEYCTL_MOVE_EXCL))
		goto error;

	ret = __key_link_check_restriction(to_keyring, key);
	if (ret < 0)
		goto error;
	ret = __key_link_check_live_key(to_keyring, key);
	if (ret < 0)
		goto error;

	__key_unlink(from_keyring, key, &from_edit);
	__key_link(key, &to_edit);
error:
	__key_link_end(to_keyring, &key->index_key, to_edit);
	__key_unlink_end(from_keyring, key, from_edit);
out:
	kleave(" = %d", ret);
	return ret;
}