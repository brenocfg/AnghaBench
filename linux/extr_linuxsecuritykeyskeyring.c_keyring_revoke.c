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
struct key {int /*<<< orphan*/  keys; } ;
struct assoc_array_edit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct assoc_array_edit*) ; 
 int /*<<< orphan*/  assoc_array_apply_edit (struct assoc_array_edit*) ; 
 struct assoc_array_edit* assoc_array_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_payload_reserve (struct key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keyring_assoc_array_ops ; 

__attribute__((used)) static void keyring_revoke(struct key *keyring)
{
	struct assoc_array_edit *edit;

	edit = assoc_array_clear(&keyring->keys, &keyring_assoc_array_ops);
	if (!IS_ERR(edit)) {
		if (edit)
			assoc_array_apply_edit(edit);
		key_payload_reserve(keyring, 0);
	}
}