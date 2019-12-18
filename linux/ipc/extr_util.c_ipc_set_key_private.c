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
struct kern_ipc_perm {int /*<<< orphan*/  key; } ;
struct ipc_ids {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_PRIVATE ; 
 int /*<<< orphan*/  ipc_kht_remove (struct ipc_ids*,struct kern_ipc_perm*) ; 

void ipc_set_key_private(struct ipc_ids *ids, struct kern_ipc_perm *ipcp)
{
	ipc_kht_remove(ids, ipcp);
	ipcp->key = IPC_PRIVATE;
}