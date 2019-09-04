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
struct user_key_payload {int /*<<< orphan*/  rcu; } ;
struct key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_payload_reserve (struct key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_keypointer (struct key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_free_payload_rcu ; 
 struct user_key_payload* user_key_payload_locked (struct key*) ; 

void user_revoke(struct key *key)
{
	struct user_key_payload *upayload = user_key_payload_locked(key);

	/* clear the quota */
	key_payload_reserve(key, 0);

	if (upayload) {
		rcu_assign_keypointer(key, NULL);
		call_rcu(&upayload->rcu, user_free_payload_rcu);
	}
}