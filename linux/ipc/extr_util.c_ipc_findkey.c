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
struct kern_ipc_perm {int dummy; } ;
struct ipc_ids {int /*<<< orphan*/  key_ht; } ;
typedef  int /*<<< orphan*/  key_t ;

/* Variables and functions */
 int /*<<< orphan*/  ipc_kht_params ; 
 int /*<<< orphan*/  ipc_lock_object (struct kern_ipc_perm*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 struct kern_ipc_perm* rhashtable_lookup_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kern_ipc_perm *ipc_findkey(struct ipc_ids *ids, key_t key)
{
	struct kern_ipc_perm *ipcp;

	ipcp = rhashtable_lookup_fast(&ids->key_ht, &key,
					      ipc_kht_params);
	if (!ipcp)
		return NULL;

	rcu_read_lock();
	ipc_lock_object(ipcp);
	return ipcp;
}