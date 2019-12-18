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
struct nfs4_exception {int interruptible; scalar_t__ retry; int /*<<< orphan*/  inode; struct nfs4_state* state; } ;
struct file_lock {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int NFS4ERR_DENIED ; 
 int /*<<< orphan*/  NFS_SERVER (int /*<<< orphan*/ ) ; 
 int _nfs4_proc_setlk (struct nfs4_state*,int,struct file_lock*) ; 
 int nfs4_handle_exception (int /*<<< orphan*/ ,int,struct nfs4_exception*) ; 

__attribute__((used)) static int nfs4_proc_setlk(struct nfs4_state *state, int cmd, struct file_lock *request)
{
	struct nfs4_exception exception = {
		.state = state,
		.inode = state->inode,
		.interruptible = true,
	};
	int err;

	do {
		err = _nfs4_proc_setlk(state, cmd, request);
		if (err == -NFS4ERR_DENIED)
			err = -EAGAIN;
		err = nfs4_handle_exception(NFS_SERVER(state->inode),
				err, &exception);
	} while (exception.retry);
	return err;
}