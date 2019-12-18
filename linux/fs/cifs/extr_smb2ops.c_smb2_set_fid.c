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
struct cifs_fid {int /*<<< orphan*/  create_guid; int /*<<< orphan*/  purge_cache; int /*<<< orphan*/  epoch; int /*<<< orphan*/  mid; int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; } ;
struct cifsInodeInfo {int /*<<< orphan*/  can_cache_brlcks; } ;
struct TYPE_7__ {int /*<<< orphan*/  create_guid; int /*<<< orphan*/  mid; int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; } ;
struct cifsFileInfo {TYPE_3__ fid; int /*<<< orphan*/  tlink; int /*<<< orphan*/  dentry; } ;
struct TCP_Server_Info {TYPE_2__* ops; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_8__ {TYPE_1__* ses; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_oplock_level ) (struct cifsInodeInfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {struct TCP_Server_Info* server; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_CACHE_WRITE (struct cifsInodeInfo*) ; 
 struct cifsInodeInfo* CIFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct cifsInodeInfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* tlink_tcon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
smb2_set_fid(struct cifsFileInfo *cfile, struct cifs_fid *fid, __u32 oplock)
{
	struct cifsInodeInfo *cinode = CIFS_I(d_inode(cfile->dentry));
	struct TCP_Server_Info *server = tlink_tcon(cfile->tlink)->ses->server;

	cfile->fid.persistent_fid = fid->persistent_fid;
	cfile->fid.volatile_fid = fid->volatile_fid;
#ifdef CONFIG_CIFS_DEBUG2
	cfile->fid.mid = fid->mid;
#endif /* CIFS_DEBUG2 */
	server->ops->set_oplock_level(cinode, oplock, fid->epoch,
				      &fid->purge_cache);
	cinode->can_cache_brlcks = CIFS_CACHE_WRITE(cinode);
	memcpy(cfile->fid.create_guid, fid->create_guid, 16);
}