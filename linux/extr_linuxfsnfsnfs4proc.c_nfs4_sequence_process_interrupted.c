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
struct rpc_cred {int dummy; } ;
struct nfs_client {int dummy; } ;
struct nfs4_slot {scalar_t__ interrupted; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static void
nfs4_sequence_process_interrupted(struct nfs_client *client,
		struct nfs4_slot *slot, struct rpc_cred *cred)
{
	WARN_ON_ONCE(1);
	slot->interrupted = 0;
}