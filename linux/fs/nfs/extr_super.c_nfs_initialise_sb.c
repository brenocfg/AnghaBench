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
struct super_block {int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_dev; int /*<<< orphan*/  s_id; int /*<<< orphan*/  s_magic; } ;
struct nfs_server {int /*<<< orphan*/  maxfilesize; int /*<<< orphan*/  wsize; } ;

/* Variables and functions */
 int MAJOR (int /*<<< orphan*/ ) ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 struct nfs_server* NFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  NFS_SUPER_MAGIC ; 
 int /*<<< orphan*/  nfs_block_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_super_set_maxbytes (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 

__attribute__((used)) static void nfs_initialise_sb(struct super_block *sb)
{
	struct nfs_server *server = NFS_SB(sb);

	sb->s_magic = NFS_SUPER_MAGIC;

	/* We probably want something more informative here */
	snprintf(sb->s_id, sizeof(sb->s_id),
		 "%u:%u", MAJOR(sb->s_dev), MINOR(sb->s_dev));

	if (sb->s_blocksize == 0)
		sb->s_blocksize = nfs_block_bits(server->wsize,
						 &sb->s_blocksize_bits);

	nfs_super_set_maxbytes(sb, server->maxfilesize);
}