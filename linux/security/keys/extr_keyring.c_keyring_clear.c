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
struct key {int /*<<< orphan*/  sem; int /*<<< orphan*/  keys; int /*<<< orphan*/ * type; } ;
struct assoc_array_edit {int dummy; } ;

/* Variables and functions */
 int ENOTDIR ; 
 scalar_t__ IS_ERR (struct assoc_array_edit*) ; 
 int PTR_ERR (struct assoc_array_edit*) ; 
 int /*<<< orphan*/  assoc_array_apply_edit (struct assoc_array_edit*) ; 
 struct assoc_array_edit* assoc_array_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_payload_reserve (struct key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_type_keyring ; 
 int /*<<< orphan*/  keyring_assoc_array_ops ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int keyring_clear(struct key *keyring)
{
	struct assoc_array_edit *edit;
	int ret;

	if (keyring->type != &key_type_keyring)
		return -ENOTDIR;

	down_write(&keyring->sem);

	edit = assoc_array_clear(&keyring->keys, &keyring_assoc_array_ops);
	if (IS_ERR(edit)) {
		ret = PTR_ERR(edit);
	} else {
		if (edit)
			assoc_array_apply_edit(edit);
		key_payload_reserve(keyring, 0);
		ret = 0;
	}

	up_write(&keyring->sem);
	return ret;
}