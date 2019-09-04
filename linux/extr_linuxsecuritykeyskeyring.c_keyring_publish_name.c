#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct key {int /*<<< orphan*/  name_link; scalar_t__ description; } ;
struct TYPE_4__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (TYPE_1__*) ; 
 int keyring_hash (scalar_t__) ; 
 TYPE_1__* keyring_name_hash ; 
 int /*<<< orphan*/  keyring_name_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void keyring_publish_name(struct key *keyring)
{
	int bucket;

	if (keyring->description) {
		bucket = keyring_hash(keyring->description);

		write_lock(&keyring_name_lock);

		if (!keyring_name_hash[bucket].next)
			INIT_LIST_HEAD(&keyring_name_hash[bucket]);

		list_add_tail(&keyring->name_link,
			      &keyring_name_hash[bucket]);

		write_unlock(&keyring_name_lock);
	}
}