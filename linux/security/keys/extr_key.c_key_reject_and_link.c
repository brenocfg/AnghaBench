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
struct key {scalar_t__ state; unsigned int expiry; int /*<<< orphan*/  flags; int /*<<< orphan*/  index_key; TYPE_1__* user; scalar_t__ restrict_link; } ;
struct assoc_array_edit {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nikeys; } ;

/* Variables and functions */
 int EBUSY ; 
 int EPERM ; 
 int /*<<< orphan*/  KEY_FLAG_USER_CONSTRUCT ; 
 scalar_t__ KEY_IS_UNINSTANTIATED ; 
 int /*<<< orphan*/  __key_link (struct key*,struct assoc_array_edit**) ; 
 int __key_link_begin (struct key*,int /*<<< orphan*/ *,struct assoc_array_edit**) ; 
 int /*<<< orphan*/  __key_link_end (struct key*,int /*<<< orphan*/ *,struct assoc_array_edit*) ; 
 int __key_link_lock (struct key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_check (struct key*) ; 
 int /*<<< orphan*/  key_construction_mutex ; 
 unsigned int key_gc_delay ; 
 int /*<<< orphan*/  key_invalidate (struct key*) ; 
 int /*<<< orphan*/  key_schedule_gc (unsigned int) ; 
 unsigned int ktime_get_real_seconds () ; 
 int /*<<< orphan*/  mark_key_instantiated (struct key*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int key_reject_and_link(struct key *key,
			unsigned timeout,
			unsigned error,
			struct key *keyring,
			struct key *authkey)
{
	struct assoc_array_edit *edit = NULL;
	int ret, awaken, link_ret = 0;

	key_check(key);
	key_check(keyring);

	awaken = 0;
	ret = -EBUSY;

	if (keyring) {
		if (keyring->restrict_link)
			return -EPERM;

		link_ret = __key_link_lock(keyring, &key->index_key);
		if (link_ret == 0) {
			link_ret = __key_link_begin(keyring, &key->index_key, &edit);
			if (link_ret < 0)
				__key_link_end(keyring, &key->index_key, edit);
		}
	}

	mutex_lock(&key_construction_mutex);

	/* can't instantiate twice */
	if (key->state == KEY_IS_UNINSTANTIATED) {
		/* mark the key as being negatively instantiated */
		atomic_inc(&key->user->nikeys);
		mark_key_instantiated(key, -error);
		key->expiry = ktime_get_real_seconds() + timeout;
		key_schedule_gc(key->expiry + key_gc_delay);

		if (test_and_clear_bit(KEY_FLAG_USER_CONSTRUCT, &key->flags))
			awaken = 1;

		ret = 0;

		/* and link it into the destination keyring */
		if (keyring && link_ret == 0)
			__key_link(key, &edit);

		/* disable the authorisation key */
		if (authkey)
			key_invalidate(authkey);
	}

	mutex_unlock(&key_construction_mutex);

	if (keyring && link_ret == 0)
		__key_link_end(keyring, &key->index_key, edit);

	/* wake up anyone waiting for a key to be constructed */
	if (awaken)
		wake_up_bit(&key->flags, KEY_FLAG_USER_CONSTRUCT);

	return ret == 0 ? link_ret : ret;
}