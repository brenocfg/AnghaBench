#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct key_preparsed_payload {scalar_t__ expiry; } ;
struct key {scalar_t__ state; scalar_t__ expiry; int /*<<< orphan*/  flags; TYPE_2__* user; TYPE_1__* type; } ;
struct assoc_array_edit {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  nikeys; } ;
struct TYPE_3__ {int (* instantiate ) (struct key*,struct key_preparsed_payload*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  KEY_FLAG_KEEP ; 
 int /*<<< orphan*/  KEY_FLAG_USER_CONSTRUCT ; 
 scalar_t__ KEY_IS_UNINSTANTIATED ; 
 scalar_t__ TIME64_MAX ; 
 int /*<<< orphan*/  __key_link (struct key*,struct assoc_array_edit**) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_check (struct key*) ; 
 int /*<<< orphan*/  key_construction_mutex ; 
 scalar_t__ key_gc_delay ; 
 int /*<<< orphan*/  key_invalidate (struct key*) ; 
 int /*<<< orphan*/  key_schedule_gc (scalar_t__) ; 
 int /*<<< orphan*/  mark_key_instantiated (struct key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct key*,struct key_preparsed_payload*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __key_instantiate_and_link(struct key *key,
				      struct key_preparsed_payload *prep,
				      struct key *keyring,
				      struct key *authkey,
				      struct assoc_array_edit **_edit)
{
	int ret, awaken;

	key_check(key);
	key_check(keyring);

	awaken = 0;
	ret = -EBUSY;

	mutex_lock(&key_construction_mutex);

	/* can't instantiate twice */
	if (key->state == KEY_IS_UNINSTANTIATED) {
		/* instantiate the key */
		ret = key->type->instantiate(key, prep);

		if (ret == 0) {
			/* mark the key as being instantiated */
			atomic_inc(&key->user->nikeys);
			mark_key_instantiated(key, 0);

			if (test_and_clear_bit(KEY_FLAG_USER_CONSTRUCT, &key->flags))
				awaken = 1;

			/* and link it into the destination keyring */
			if (keyring) {
				if (test_bit(KEY_FLAG_KEEP, &keyring->flags))
					set_bit(KEY_FLAG_KEEP, &key->flags);

				__key_link(key, _edit);
			}

			/* disable the authorisation key */
			if (authkey)
				key_invalidate(authkey);

			if (prep->expiry != TIME64_MAX) {
				key->expiry = prep->expiry;
				key_schedule_gc(prep->expiry + key_gc_delay);
			}
		}
	}

	mutex_unlock(&key_construction_mutex);

	/* wake up anyone waiting for a key to be constructed */
	if (awaken)
		wake_up_bit(&key->flags, KEY_FLAG_USER_CONSTRUCT);

	return ret;
}