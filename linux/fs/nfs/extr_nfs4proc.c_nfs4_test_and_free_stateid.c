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
struct nfs_server {TYPE_1__* nfs_client; } ;
struct nfs4_minor_version_ops {int /*<<< orphan*/  (* test_and_free_expired ) (struct nfs_server*,int /*<<< orphan*/ *,struct cred const*) ;} ;
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
struct TYPE_2__ {struct nfs4_minor_version_ops* cl_mvops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nfs_server*,int /*<<< orphan*/ *,struct cred const*) ; 

__attribute__((used)) static void nfs4_test_and_free_stateid(struct nfs_server *server,
		nfs4_stateid *stateid,
		const struct cred *cred)
{
	const struct nfs4_minor_version_ops *ops = server->nfs_client->cl_mvops;

	ops->test_and_free_expired(server, stateid, cred);
}