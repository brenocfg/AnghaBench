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
struct nfs_server {int dummy; } ;
struct nfs_fh {int dummy; } ;
struct nfs4_exception {int interruptible; scalar_t__ retry; } ;

/* Variables and functions */
 int /*<<< orphan*/  _nfs4_server_capabilities (struct nfs_server*,struct nfs_fh*) ; 
 int nfs4_handle_exception (struct nfs_server*,int /*<<< orphan*/ ,struct nfs4_exception*) ; 

int nfs4_server_capabilities(struct nfs_server *server, struct nfs_fh *fhandle)
{
	struct nfs4_exception exception = {
		.interruptible = true,
	};
	int err;
	do {
		err = nfs4_handle_exception(server,
				_nfs4_server_capabilities(server, fhandle),
				&exception);
	} while (exception.retry);
	return err;
}