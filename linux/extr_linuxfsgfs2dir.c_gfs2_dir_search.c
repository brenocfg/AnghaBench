#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct qstr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  no_formal_ino; int /*<<< orphan*/  no_addr; } ;
struct inode {int /*<<< orphan*/  i_sb; TYPE_1__ de_inum; int /*<<< orphan*/  de_rahead; int /*<<< orphan*/  de_type; } ;
struct gfs2_dirent {int /*<<< orphan*/  i_sb; TYPE_1__ de_inum; int /*<<< orphan*/  de_rahead; int /*<<< orphan*/  de_type; } ;
struct buffer_head {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_rahead; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  ENOENT ; 
 struct inode* ERR_CAST (struct inode*) ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFS2_BLKST_FREE ; 
 TYPE_2__* GFS2_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_dirent_find ; 
 struct inode* gfs2_dirent_search (struct inode*,struct qstr const*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 struct inode* gfs2_inode_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct inode *gfs2_dir_search(struct inode *dir, const struct qstr *name,
			      bool fail_on_exist)
{
	struct buffer_head *bh;
	struct gfs2_dirent *dent;
	u64 addr, formal_ino;
	u16 dtype;

	dent = gfs2_dirent_search(dir, name, gfs2_dirent_find, &bh);
	if (dent) {
		struct inode *inode;
		u16 rahead;

		if (IS_ERR(dent))
			return ERR_CAST(dent);
		dtype = be16_to_cpu(dent->de_type);
		rahead = be16_to_cpu(dent->de_rahead);
		addr = be64_to_cpu(dent->de_inum.no_addr);
		formal_ino = be64_to_cpu(dent->de_inum.no_formal_ino);
		brelse(bh);
		if (fail_on_exist)
			return ERR_PTR(-EEXIST);
		inode = gfs2_inode_lookup(dir->i_sb, dtype, addr, formal_ino,
					  GFS2_BLKST_FREE /* ignore */);
		if (!IS_ERR(inode))
			GFS2_I(inode)->i_rahead = rahead;
		return inode;
	}
	return ERR_PTR(-ENOENT);
}