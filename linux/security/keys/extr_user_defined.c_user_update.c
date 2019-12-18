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
struct user_key_payload {int /*<<< orphan*/  rcu; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** data; } ;
struct key_preparsed_payload {TYPE_1__ payload; int /*<<< orphan*/  expiry; int /*<<< orphan*/  datalen; } ;
struct key {int /*<<< orphan*/  expiry; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct user_key_payload* dereference_key_locked (struct key*) ; 
 scalar_t__ key_is_positive (struct key*) ; 
 int key_payload_reserve (struct key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_keypointer (struct key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_free_payload_rcu ; 

int user_update(struct key *key, struct key_preparsed_payload *prep)
{
	struct user_key_payload *zap = NULL;
	int ret;

	/* check the quota and attach the new data */
	ret = key_payload_reserve(key, prep->datalen);
	if (ret < 0)
		return ret;

	/* attach the new data, displacing the old */
	key->expiry = prep->expiry;
	if (key_is_positive(key))
		zap = dereference_key_locked(key);
	rcu_assign_keypointer(key, prep->payload.data[0]);
	prep->payload.data[0] = NULL;

	if (zap)
		call_rcu(&zap->rcu, user_free_payload_rcu);
	return ret;
}