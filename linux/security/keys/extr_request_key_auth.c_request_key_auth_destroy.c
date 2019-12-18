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
struct request_key_auth {int /*<<< orphan*/  rcu; } ;
struct TYPE_2__ {int /*<<< orphan*/  rcu_data0; } ;
struct key {int /*<<< orphan*/  serial; TYPE_1__ payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ) ; 
 struct request_key_auth* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_keypointer (struct key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_key_auth_rcu_disposal ; 

__attribute__((used)) static void request_key_auth_destroy(struct key *key)
{
	struct request_key_auth *rka = rcu_access_pointer(key->payload.rcu_data0);

	kenter("{%d}", key->serial);
	if (rka) {
		rcu_assign_keypointer(key, NULL);
		call_rcu(&rka->rcu, request_key_auth_rcu_disposal);
	}
}