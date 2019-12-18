#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nfs_server {int dummy; } ;
struct cred {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_REVOKED_STATEID_TYPE ; 
 int /*<<< orphan*/  nfs4_test_and_free_stateid (struct nfs_server*,TYPE_1__*,struct cred const*) ; 

__attribute__((used)) static void __nfs4_free_revoked_stateid(struct nfs_server *server,
		nfs4_stateid *stateid,
		const struct cred *cred)
{
	stateid->type = NFS4_REVOKED_STATEID_TYPE;
	nfs4_test_and_free_stateid(server, stateid, cred);
}