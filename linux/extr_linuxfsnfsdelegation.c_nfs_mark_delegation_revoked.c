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
struct nfs_server {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct nfs_delegation {TYPE_1__ stateid; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_INVALID_STATEID_TYPE ; 
 int /*<<< orphan*/  NFS_DELEGATION_REVOKED ; 
 int /*<<< orphan*/  nfs_mark_return_delegation (struct nfs_server*,struct nfs_delegation*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_mark_delegation_revoked(struct nfs_server *server,
		struct nfs_delegation *delegation)
{
	set_bit(NFS_DELEGATION_REVOKED, &delegation->flags);
	delegation->stateid.type = NFS4_INVALID_STATEID_TYPE;
	nfs_mark_return_delegation(server, delegation);
}