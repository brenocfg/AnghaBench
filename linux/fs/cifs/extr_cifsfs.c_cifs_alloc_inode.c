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
struct super_block {int dummy; } ;
struct inode {int i_blkbits; } ;
struct cifsInodeInfo {int cifsAttrs; struct inode vfs_inode; int /*<<< orphan*/  llist; int /*<<< orphan*/  openFileList; int /*<<< orphan*/  lease_key; int /*<<< orphan*/  open_file_lock; scalar_t__ epoch; scalar_t__ createtime; scalar_t__ uniqueid; scalar_t__ server_eof; scalar_t__ writers; int /*<<< orphan*/  writers_lock; scalar_t__ flags; scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_inode_cachep ; 
 int /*<<< orphan*/  cifs_set_oplock_level (struct cifsInodeInfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_random_uuid (int /*<<< orphan*/ ) ; 
 struct cifsInodeInfo* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct inode *
cifs_alloc_inode(struct super_block *sb)
{
	struct cifsInodeInfo *cifs_inode;
	cifs_inode = kmem_cache_alloc(cifs_inode_cachep, GFP_KERNEL);
	if (!cifs_inode)
		return NULL;
	cifs_inode->cifsAttrs = 0x20;	/* default */
	cifs_inode->time = 0;
	/*
	 * Until the file is open and we have gotten oplock info back from the
	 * server, can not assume caching of file data or metadata.
	 */
	cifs_set_oplock_level(cifs_inode, 0);
	cifs_inode->flags = 0;
	spin_lock_init(&cifs_inode->writers_lock);
	cifs_inode->writers = 0;
	cifs_inode->vfs_inode.i_blkbits = 14;  /* 2**14 = CIFS_MAX_MSGSIZE */
	cifs_inode->server_eof = 0;
	cifs_inode->uniqueid = 0;
	cifs_inode->createtime = 0;
	cifs_inode->epoch = 0;
	spin_lock_init(&cifs_inode->open_file_lock);
	generate_random_uuid(cifs_inode->lease_key);

	/*
	 * Can not set i_flags here - they get immediately overwritten to zero
	 * by the VFS.
	 */
	/* cifs_inode->vfs_inode.i_flags = S_NOATIME | S_NOCMTIME; */
	INIT_LIST_HEAD(&cifs_inode->openFileList);
	INIT_LIST_HEAD(&cifs_inode->llist);
	return &cifs_inode->vfs_inode;
}