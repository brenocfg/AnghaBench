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
struct kern_ipc_perm {scalar_t__ key; int /*<<< orphan*/  khtnode; } ;
struct ipc_ids {int /*<<< orphan*/  key_ht; } ;

/* Variables and functions */
 scalar_t__ IPC_PRIVATE ; 
 int /*<<< orphan*/  ipc_kht_params ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipc_kht_remove(struct ipc_ids *ids, struct kern_ipc_perm *ipcp)
{
	if (ipcp->key != IPC_PRIVATE)
		rhashtable_remove_fast(&ids->key_ht, &ipcp->khtnode,
				       ipc_kht_params);
}