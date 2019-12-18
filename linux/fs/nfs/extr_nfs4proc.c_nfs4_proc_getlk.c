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
struct nfs4_state {int /*<<< orphan*/  inode; } ;
struct nfs4_exception {int interruptible; scalar_t__ retry; } ;
struct file_lock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_SERVER (int /*<<< orphan*/ ) ; 
 int _nfs4_proc_getlk (struct nfs4_state*,int,struct file_lock*) ; 
 int nfs4_handle_exception (int /*<<< orphan*/ ,int,struct nfs4_exception*) ; 
 int /*<<< orphan*/  trace_nfs4_get_lock (struct file_lock*,struct nfs4_state*,int,int) ; 

__attribute__((used)) static int nfs4_proc_getlk(struct nfs4_state *state, int cmd, struct file_lock *request)
{
	struct nfs4_exception exception = {
		.interruptible = true,
	};
	int err;

	do {
		err = _nfs4_proc_getlk(state, cmd, request);
		trace_nfs4_get_lock(request, state, cmd, err);
		err = nfs4_handle_exception(NFS_SERVER(state->inode), err,
				&exception);
	} while (exception.retry);
	return err;
}