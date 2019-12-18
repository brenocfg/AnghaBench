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
struct nfs_server {int /*<<< orphan*/  mig_status; struct nfs_client* nfs_client; } ;
struct nfs_client {int dummy; } ;
struct nfs4_exception {int retry; scalar_t__ recovering; int /*<<< orphan*/  interruptible; int /*<<< orphan*/  timeout; scalar_t__ delay; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NFS_MIG_FAILED ; 
 int nfs4_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nfs4_do_handle_exception (struct nfs_server*,int,struct nfs4_exception*) ; 
 int nfs4_wait_clnt_recover (struct nfs_client*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nfs4_handle_exception(struct nfs_server *server, int errorcode, struct nfs4_exception *exception)
{
	struct nfs_client *clp = server->nfs_client;
	int ret;

	ret = nfs4_do_handle_exception(server, errorcode, exception);
	if (exception->delay) {
		ret = nfs4_delay(&exception->timeout,
				exception->interruptible);
		goto out_retry;
	}
	if (exception->recovering) {
		ret = nfs4_wait_clnt_recover(clp);
		if (test_bit(NFS_MIG_FAILED, &server->mig_status))
			return -EIO;
		goto out_retry;
	}
	return ret;
out_retry:
	if (ret == 0)
		exception->retry = 1;
	return ret;
}