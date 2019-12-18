#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kiocb {int /*<<< orphan*/  ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct file {TYPE_1__* f_mapping; scalar_t__ private_data; } ;
struct cifsInodeInfo {int /*<<< orphan*/  lock_sem; } ;
struct cifsFileInfo {int /*<<< orphan*/  tlink; } ;
struct TCP_Server_Info {TYPE_3__* vals; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_8__ {TYPE_2__* ses; } ;
struct TYPE_7__ {int /*<<< orphan*/  exclusive_lock_type; } ;
struct TYPE_6__ {struct TCP_Server_Info* server; } ;
struct TYPE_5__ {struct inode* host; } ;

/* Variables and functions */
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 int /*<<< orphan*/  CIFS_WRITE_OP ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  __generic_file_write_iter (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  cifs_find_lock_conflict (struct cifsFileInfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generic_write_checks (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  generic_write_sync (struct kiocb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 TYPE_4__* tlink_tcon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
cifs_writev(struct kiocb *iocb, struct iov_iter *from)
{
	struct file *file = iocb->ki_filp;
	struct cifsFileInfo *cfile = (struct cifsFileInfo *)file->private_data;
	struct inode *inode = file->f_mapping->host;
	struct cifsInodeInfo *cinode = CIFS_I(inode);
	struct TCP_Server_Info *server = tlink_tcon(cfile->tlink)->ses->server;
	ssize_t rc;

	inode_lock(inode);
	/*
	 * We need to hold the sem to be sure nobody modifies lock list
	 * with a brlock that prevents writing.
	 */
	down_read(&cinode->lock_sem);

	rc = generic_write_checks(iocb, from);
	if (rc <= 0)
		goto out;

	if (!cifs_find_lock_conflict(cfile, iocb->ki_pos, iov_iter_count(from),
				     server->vals->exclusive_lock_type, 0,
				     NULL, CIFS_WRITE_OP))
		rc = __generic_file_write_iter(iocb, from);
	else
		rc = -EACCES;
out:
	up_read(&cinode->lock_sem);
	inode_unlock(inode);

	if (rc > 0)
		rc = generic_write_sync(iocb, rc);
	return rc;
}