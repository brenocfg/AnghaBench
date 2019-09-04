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
struct cifs_fid {int /*<<< orphan*/  netfid; } ;
struct cifsInodeInfo {int /*<<< orphan*/  can_cache_brlcks; } ;
struct TYPE_2__ {int /*<<< orphan*/  netfid; } ;
struct cifsFileInfo {TYPE_1__ fid; int /*<<< orphan*/  dentry; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_CACHE_WRITE (struct cifsInodeInfo*) ; 
 struct cifsInodeInfo* CIFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_set_oplock_level (struct cifsInodeInfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cifs_set_fid(struct cifsFileInfo *cfile, struct cifs_fid *fid, __u32 oplock)
{
	struct cifsInodeInfo *cinode = CIFS_I(d_inode(cfile->dentry));
	cfile->fid.netfid = fid->netfid;
	cifs_set_oplock_level(cinode, oplock);
	cinode->can_cache_brlcks = CIFS_CACHE_WRITE(cinode);
}