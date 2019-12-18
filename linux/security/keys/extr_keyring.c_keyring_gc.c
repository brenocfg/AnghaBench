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
typedef  int /*<<< orphan*/  time64_t ;
struct key {int flags; int /*<<< orphan*/  sem; int /*<<< orphan*/  keys; scalar_t__ description; int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 int KEY_FLAG_INVALIDATED ; 
 int KEY_FLAG_REVOKED ; 
 int /*<<< orphan*/  assoc_array_gc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int assoc_array_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  keyring_assoc_array_ops ; 
 int /*<<< orphan*/  keyring_gc_check_iterator ; 
 int /*<<< orphan*/  keyring_gc_select_iterator ; 
 int /*<<< orphan*/  kleave (char*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void keyring_gc(struct key *keyring, time64_t limit)
{
	int result;

	kenter("%x{%s}", keyring->serial, keyring->description ?: "");

	if (keyring->flags & ((1 << KEY_FLAG_INVALIDATED) |
			      (1 << KEY_FLAG_REVOKED)))
		goto dont_gc;

	/* scan the keyring looking for dead keys */
	rcu_read_lock();
	result = assoc_array_iterate(&keyring->keys,
				     keyring_gc_check_iterator, &limit);
	rcu_read_unlock();
	if (result == true)
		goto do_gc;

dont_gc:
	kleave(" [no gc]");
	return;

do_gc:
	down_write(&keyring->sem);
	assoc_array_gc(&keyring->keys, &keyring_assoc_array_ops,
		       keyring_gc_select_iterator, &limit);
	up_write(&keyring->sem);
	kleave(" [gc]");
}