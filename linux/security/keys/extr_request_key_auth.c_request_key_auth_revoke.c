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
struct request_key_auth {int /*<<< orphan*/  rcu; } ;
struct key {int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct request_key_auth* dereference_key_locked (struct key*) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_keypointer (struct key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_key_auth_rcu_disposal ; 

__attribute__((used)) static void request_key_auth_revoke(struct key *key)
{
	struct request_key_auth *rka = dereference_key_locked(key);

	kenter("{%d}", key->serial);
	rcu_assign_keypointer(key, NULL);
	call_rcu(&rka->rcu, request_key_auth_rcu_disposal);
}