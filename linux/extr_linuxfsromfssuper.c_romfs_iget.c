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
typedef  int /*<<< orphan*/  umode_t ;
struct super_block {int dummy; } ;
struct romfs_inode_info {unsigned long i_metasize; unsigned long i_dataoffset; } ;
struct romfs_inode {int /*<<< orphan*/  spec; int /*<<< orphan*/  size; int /*<<< orphan*/  next; } ;
struct TYPE_8__ {int /*<<< orphan*/ * a_ops; } ;
struct TYPE_7__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_6__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_5__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct inode {int i_state; unsigned long i_size; int /*<<< orphan*/  i_mode; TYPE_4__ i_data; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; TYPE_3__ i_ctime; TYPE_2__ i_atime; TYPE_1__ i_mtime; } ;
typedef  int /*<<< orphan*/  ri ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 scalar_t__ IS_ERR_VALUE (unsigned long) ; 
 int I_NEW ; 
 int /*<<< orphan*/  MKDEV (unsigned int,unsigned int) ; 
#define  ROMFH_DIR 130 
 unsigned int ROMFH_EXEC ; 
 unsigned int ROMFH_HRD ; 
 unsigned long ROMFH_MASK ; 
 unsigned long ROMFH_PAD ; 
#define  ROMFH_REG 129 
 unsigned long ROMFH_SIZE ; 
#define  ROMFH_SYM 128 
 unsigned int ROMFH_TYPE ; 
 struct romfs_inode_info* ROMFS_I (struct inode*) ; 
 int /*<<< orphan*/  ROMFS_MAXFN ; 
 int /*<<< orphan*/  S_IRWXUGO ; 
 int /*<<< orphan*/  S_IXUGO ; 
 unsigned long be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct inode* iget_locked (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_nohighmem (struct inode*) ; 
 int /*<<< orphan*/  page_symlink_inode_operations ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long) ; 
 int /*<<< orphan*/  romfs_aops ; 
 int romfs_dev_read (struct super_block*,unsigned long,struct romfs_inode*,int) ; 
 unsigned long romfs_dev_strnlen (struct super_block*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  romfs_dir_inode_operations ; 
 int /*<<< orphan*/  romfs_dir_operations ; 
 int /*<<< orphan*/ * romfs_modemap ; 
 int /*<<< orphan*/  romfs_ro_fops ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static struct inode *romfs_iget(struct super_block *sb, unsigned long pos)
{
	struct romfs_inode_info *inode;
	struct romfs_inode ri;
	struct inode *i;
	unsigned long nlen;
	unsigned nextfh;
	int ret;
	umode_t mode;

	/* we might have to traverse a chain of "hard link" file entries to get
	 * to the actual file */
	for (;;) {
		ret = romfs_dev_read(sb, pos, &ri, sizeof(ri));
		if (ret < 0)
			goto error;

		/* XXX: do romfs_checksum here too (with name) */

		nextfh = be32_to_cpu(ri.next);
		if ((nextfh & ROMFH_TYPE) != ROMFH_HRD)
			break;

		pos = be32_to_cpu(ri.spec) & ROMFH_MASK;
	}

	/* determine the length of the filename */
	nlen = romfs_dev_strnlen(sb, pos + ROMFH_SIZE, ROMFS_MAXFN);
	if (IS_ERR_VALUE(nlen))
		goto eio;

	/* get an inode for this image position */
	i = iget_locked(sb, pos);
	if (!i)
		return ERR_PTR(-ENOMEM);

	if (!(i->i_state & I_NEW))
		return i;

	/* precalculate the data offset */
	inode = ROMFS_I(i);
	inode->i_metasize = (ROMFH_SIZE + nlen + 1 + ROMFH_PAD) & ROMFH_MASK;
	inode->i_dataoffset = pos + inode->i_metasize;

	set_nlink(i, 1);		/* Hard to decide.. */
	i->i_size = be32_to_cpu(ri.size);
	i->i_mtime.tv_sec = i->i_atime.tv_sec = i->i_ctime.tv_sec = 0;
	i->i_mtime.tv_nsec = i->i_atime.tv_nsec = i->i_ctime.tv_nsec = 0;

	/* set up mode and ops */
	mode = romfs_modemap[nextfh & ROMFH_TYPE];

	switch (nextfh & ROMFH_TYPE) {
	case ROMFH_DIR:
		i->i_size = ROMFS_I(i)->i_metasize;
		i->i_op = &romfs_dir_inode_operations;
		i->i_fop = &romfs_dir_operations;
		if (nextfh & ROMFH_EXEC)
			mode |= S_IXUGO;
		break;
	case ROMFH_REG:
		i->i_fop = &romfs_ro_fops;
		i->i_data.a_ops = &romfs_aops;
		if (nextfh & ROMFH_EXEC)
			mode |= S_IXUGO;
		break;
	case ROMFH_SYM:
		i->i_op = &page_symlink_inode_operations;
		inode_nohighmem(i);
		i->i_data.a_ops = &romfs_aops;
		mode |= S_IRWXUGO;
		break;
	default:
		/* depending on MBZ for sock/fifos */
		nextfh = be32_to_cpu(ri.spec);
		init_special_inode(i, mode, MKDEV(nextfh >> 16,
						  nextfh & 0xffff));
		break;
	}

	i->i_mode = mode;

	unlock_new_inode(i);
	return i;

eio:
	ret = -EIO;
error:
	pr_err("read error for inode 0x%lx\n", pos);
	return ERR_PTR(ret);
}