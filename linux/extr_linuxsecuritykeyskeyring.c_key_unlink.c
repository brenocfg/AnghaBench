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
struct key {int /*<<< orphan*/  sem; scalar_t__ datalen; int /*<<< orphan*/  index_key; int /*<<< orphan*/  keys; int /*<<< orphan*/ * type; } ;
struct assoc_array_edit {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOTDIR ; 
 scalar_t__ IS_ERR (struct assoc_array_edit*) ; 
 scalar_t__ KEYQUOTA_LINK_BYTES ; 
 int PTR_ERR (struct assoc_array_edit*) ; 
 int /*<<< orphan*/  assoc_array_apply_edit (struct assoc_array_edit*) ; 
 struct assoc_array_edit* assoc_array_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_check (struct key*) ; 
 int /*<<< orphan*/  key_payload_reserve (struct key*,scalar_t__) ; 
 int /*<<< orphan*/  key_type_keyring ; 
 int /*<<< orphan*/  keyring_assoc_array_ops ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int key_unlink(struct key *keyring, struct key *key)
{
	struct assoc_array_edit *edit;
	int ret;

	key_check(keyring);
	key_check(key);

	if (keyring->type != &key_type_keyring)
		return -ENOTDIR;

	down_write(&keyring->sem);

	edit = assoc_array_delete(&keyring->keys, &keyring_assoc_array_ops,
				  &key->index_key);
	if (IS_ERR(edit)) {
		ret = PTR_ERR(edit);
		goto error;
	}
	ret = -ENOENT;
	if (edit == NULL)
		goto error;

	assoc_array_apply_edit(edit);
	key_payload_reserve(keyring, keyring->datalen - KEYQUOTA_LINK_BYTES);
	ret = 0;

error:
	up_write(&keyring->sem);
	return ret;
}