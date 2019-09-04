#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct keyring_index_key {int /*<<< orphan*/  description; TYPE_1__* type; } ;
struct key {int flags; int /*<<< orphan*/  serial; int /*<<< orphan*/  keys; } ;
typedef  int /*<<< orphan*/ * key_ref_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int KEY_FLAG_INVALIDATED ; 
 int KEY_FLAG_REVOKED ; 
 int /*<<< orphan*/  __key_get (struct key*) ; 
 void* assoc_array_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct keyring_index_key const*) ; 
 int /*<<< orphan*/  is_key_possessed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct key* key_ref_to_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keyring_assoc_array_ops ; 
 struct key* keyring_ptr_to_key (void const*) ; 
 int /*<<< orphan*/  kleave (char*,...) ; 
 int /*<<< orphan*/ * make_key_ref (struct key*,int /*<<< orphan*/ ) ; 

key_ref_t find_key_to_update(key_ref_t keyring_ref,
			     const struct keyring_index_key *index_key)
{
	struct key *keyring, *key;
	const void *object;

	keyring = key_ref_to_ptr(keyring_ref);

	kenter("{%d},{%s,%s}",
	       keyring->serial, index_key->type->name, index_key->description);

	object = assoc_array_find(&keyring->keys, &keyring_assoc_array_ops,
				  index_key);

	if (object)
		goto found;

	kleave(" = NULL");
	return NULL;

found:
	key = keyring_ptr_to_key(object);
	if (key->flags & ((1 << KEY_FLAG_INVALIDATED) |
			  (1 << KEY_FLAG_REVOKED))) {
		kleave(" = NULL [x]");
		return NULL;
	}
	__key_get(key);
	kleave(" = {%d}", key->serial);
	return make_key_ref(key, is_key_possessed(keyring_ref));
}