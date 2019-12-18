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
struct tcon_link {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int f_mode; struct cifsFileInfo* private_data; int /*<<< orphan*/  f_flags; } ;
struct dentry {int dummy; } ;
struct cifs_tcon {int /*<<< orphan*/  open_file_lock; int /*<<< orphan*/  num_local_opens; int /*<<< orphan*/  openFileList; TYPE_1__* ses; } ;
struct cifs_fid_locks {int /*<<< orphan*/  llist; struct cifsFileInfo* cfile; int /*<<< orphan*/  locks; } ;
struct cifs_fid {int purge_cache; TYPE_2__* pending_open; } ;
struct cifsInodeInfo {int /*<<< orphan*/  open_file_lock; int /*<<< orphan*/  openFileList; int /*<<< orphan*/  lock_sem; int /*<<< orphan*/  llist; } ;
struct cifsFileInfo {int count; int invalidHandle; int /*<<< orphan*/  flist; int /*<<< orphan*/  tlist; int /*<<< orphan*/  file_info_lock; int /*<<< orphan*/  fh_mutex; int /*<<< orphan*/  oplock_break; int /*<<< orphan*/  tlink; int /*<<< orphan*/  f_flags; int /*<<< orphan*/  dentry; int /*<<< orphan*/  uid; int /*<<< orphan*/  pid; struct cifs_fid_locks* llist; } ;
struct TCP_Server_Info {TYPE_3__* ops; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_8__ {int /*<<< orphan*/  tgid; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_fid ) (struct cifsFileInfo*,struct cifs_fid*,scalar_t__) ;scalar_t__ (* is_read_op ) (scalar_t__) ;} ;
struct TYPE_6__ {scalar_t__ oplock; int /*<<< orphan*/  olist; } ;
struct TYPE_5__ {struct TCP_Server_Info* server; } ;

/* Variables and functions */
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 scalar_t__ CIFS_OPLOCK_NO_CHANGE ; 
 int FMODE_READ ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cifs_down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_get_tlink (struct tcon_link*) ; 
 scalar_t__ cifs_has_mand_locks (struct cifsInodeInfo*) ; 
 int /*<<< orphan*/  cifs_oplock_break ; 
 int /*<<< orphan*/  cifs_sb_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_zap_mapping (struct inode*) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  current_fsuid () ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 struct dentry* file_dentry (struct file*) ; 
 int /*<<< orphan*/  kfree (struct cifsFileInfo*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct cifsFileInfo*,struct cifs_fid*,scalar_t__) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

struct cifsFileInfo *
cifs_new_fileinfo(struct cifs_fid *fid, struct file *file,
		  struct tcon_link *tlink, __u32 oplock)
{
	struct dentry *dentry = file_dentry(file);
	struct inode *inode = d_inode(dentry);
	struct cifsInodeInfo *cinode = CIFS_I(inode);
	struct cifsFileInfo *cfile;
	struct cifs_fid_locks *fdlocks;
	struct cifs_tcon *tcon = tlink_tcon(tlink);
	struct TCP_Server_Info *server = tcon->ses->server;

	cfile = kzalloc(sizeof(struct cifsFileInfo), GFP_KERNEL);
	if (cfile == NULL)
		return cfile;

	fdlocks = kzalloc(sizeof(struct cifs_fid_locks), GFP_KERNEL);
	if (!fdlocks) {
		kfree(cfile);
		return NULL;
	}

	INIT_LIST_HEAD(&fdlocks->locks);
	fdlocks->cfile = cfile;
	cfile->llist = fdlocks;
	cifs_down_write(&cinode->lock_sem);
	list_add(&fdlocks->llist, &cinode->llist);
	up_write(&cinode->lock_sem);

	cfile->count = 1;
	cfile->pid = current->tgid;
	cfile->uid = current_fsuid();
	cfile->dentry = dget(dentry);
	cfile->f_flags = file->f_flags;
	cfile->invalidHandle = false;
	cfile->tlink = cifs_get_tlink(tlink);
	INIT_WORK(&cfile->oplock_break, cifs_oplock_break);
	mutex_init(&cfile->fh_mutex);
	spin_lock_init(&cfile->file_info_lock);

	cifs_sb_active(inode->i_sb);

	/*
	 * If the server returned a read oplock and we have mandatory brlocks,
	 * set oplock level to None.
	 */
	if (server->ops->is_read_op(oplock) && cifs_has_mand_locks(cinode)) {
		cifs_dbg(FYI, "Reset oplock val from read to None due to mand locks\n");
		oplock = 0;
	}

	spin_lock(&tcon->open_file_lock);
	if (fid->pending_open->oplock != CIFS_OPLOCK_NO_CHANGE && oplock)
		oplock = fid->pending_open->oplock;
	list_del(&fid->pending_open->olist);

	fid->purge_cache = false;
	server->ops->set_fid(cfile, fid, oplock);

	list_add(&cfile->tlist, &tcon->openFileList);
	atomic_inc(&tcon->num_local_opens);

	/* if readable file instance put first in list*/
	spin_lock(&cinode->open_file_lock);
	if (file->f_mode & FMODE_READ)
		list_add(&cfile->flist, &cinode->openFileList);
	else
		list_add_tail(&cfile->flist, &cinode->openFileList);
	spin_unlock(&cinode->open_file_lock);
	spin_unlock(&tcon->open_file_lock);

	if (fid->purge_cache)
		cifs_zap_mapping(inode);

	file->private_data = cfile;
	return cfile;
}