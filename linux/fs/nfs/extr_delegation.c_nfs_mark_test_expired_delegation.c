#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs_server {TYPE_2__* nfs_client; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct nfs_delegation {int /*<<< orphan*/  flags; TYPE_1__ stateid; } ;
struct TYPE_4__ {int /*<<< orphan*/  cl_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4CLNT_DELEGATION_EXPIRED ; 
 scalar_t__ NFS4_INVALID_STATEID_TYPE ; 
 int /*<<< orphan*/  NFS_DELEGATION_NEED_RECLAIM ; 
 int /*<<< orphan*/  NFS_DELEGATION_TEST_EXPIRED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_mark_test_expired_delegation(struct nfs_server *server,
	    struct nfs_delegation *delegation)
{
	if (delegation->stateid.type == NFS4_INVALID_STATEID_TYPE)
		return;
	clear_bit(NFS_DELEGATION_NEED_RECLAIM, &delegation->flags);
	set_bit(NFS_DELEGATION_TEST_EXPIRED, &delegation->flags);
	set_bit(NFS4CLNT_DELEGATION_EXPIRED, &server->nfs_client->cl_state);
}