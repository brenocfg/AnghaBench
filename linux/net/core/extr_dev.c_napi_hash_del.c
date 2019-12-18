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
struct napi_struct {int /*<<< orphan*/  napi_hash_node; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAPI_STATE_HASHED ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_hash_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool napi_hash_del(struct napi_struct *napi)
{
	bool rcu_sync_needed = false;

	spin_lock(&napi_hash_lock);

	if (test_and_clear_bit(NAPI_STATE_HASHED, &napi->state)) {
		rcu_sync_needed = true;
		hlist_del_rcu(&napi->napi_hash_node);
	}
	spin_unlock(&napi_hash_lock);
	return rcu_sync_needed;
}