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
struct napi_struct {size_t napi_id; int /*<<< orphan*/  napi_hash_node; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 size_t HASH_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ MIN_NAPI_ID ; 
 int /*<<< orphan*/  NAPI_STATE_HASHED ; 
 int /*<<< orphan*/  NAPI_STATE_NO_BUSY_POLL ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ napi_by_id (scalar_t__) ; 
 scalar_t__ napi_gen_id ; 
 int /*<<< orphan*/ * napi_hash ; 
 int /*<<< orphan*/  napi_hash_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void napi_hash_add(struct napi_struct *napi)
{
	if (test_bit(NAPI_STATE_NO_BUSY_POLL, &napi->state) ||
	    test_and_set_bit(NAPI_STATE_HASHED, &napi->state))
		return;

	spin_lock(&napi_hash_lock);

	/* 0..NR_CPUS range is reserved for sender_cpu use */
	do {
		if (unlikely(++napi_gen_id < MIN_NAPI_ID))
			napi_gen_id = MIN_NAPI_ID;
	} while (napi_by_id(napi_gen_id));
	napi->napi_id = napi_gen_id;

	hlist_add_head_rcu(&napi->napi_hash_node,
			   &napi_hash[napi->napi_id % HASH_SIZE(napi_hash)]);

	spin_unlock(&napi_hash_lock);
}