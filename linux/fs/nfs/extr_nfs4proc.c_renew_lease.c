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
struct nfs_server {struct nfs_client* nfs_client; } ;
struct nfs_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_renew_lease (struct nfs_client*,unsigned long) ; 
 int /*<<< orphan*/  nfs4_has_session (struct nfs_client*) ; 

__attribute__((used)) static void renew_lease(const struct nfs_server *server, unsigned long timestamp)
{
	struct nfs_client *clp = server->nfs_client;

	if (!nfs4_has_session(clp))
		do_renew_lease(clp, timestamp);
}