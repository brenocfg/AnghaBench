#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct key_restriction {int /*<<< orphan*/  key; } ;
struct TYPE_3__ {int /*<<< orphan*/ * next; } ;
struct key {int /*<<< orphan*/  keys; struct key_restriction* restrict_link; TYPE_1__ name_link; scalar_t__ description; } ;

/* Variables and functions */
 int /*<<< orphan*/  assoc_array_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keyring_assoc_array_ops ; 
 int /*<<< orphan*/  keyring_name_lock ; 
 int /*<<< orphan*/  kfree (struct key_restriction*) ; 
 int /*<<< orphan*/  list_del (TYPE_1__*) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void keyring_destroy(struct key *keyring)
{
	if (keyring->description) {
		write_lock(&keyring_name_lock);

		if (keyring->name_link.next != NULL &&
		    !list_empty(&keyring->name_link))
			list_del(&keyring->name_link);

		write_unlock(&keyring_name_lock);
	}

	if (keyring->restrict_link) {
		struct key_restriction *keyres = keyring->restrict_link;

		key_put(keyres->key);
		kfree(keyres);
	}

	assoc_array_destroy(&keyring->keys, &keyring_assoc_array_ops);
}