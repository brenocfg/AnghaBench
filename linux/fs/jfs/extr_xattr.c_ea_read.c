#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_blocksize; int s_blocksize_bits; } ;
struct metapage {int /*<<< orphan*/  data; } ;
struct jfs_sb_info {int l2nbperpage; scalar_t__ nbperpage; } ;
struct TYPE_4__ {int flag; } ;
struct jfs_inode_info {TYPE_1__ ea; } ;
struct jfs_ea_list {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
typedef  int s64 ;
typedef  int s32 ;

/* Variables and functions */
 int DXD_INLINE ; 
 int EIO ; 
 struct jfs_inode_info* JFS_IP (struct inode*) ; 
 struct jfs_sb_info* JFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  PSIZE ; 
 int addressDXD (TYPE_1__*) ; 
 int ea_read_inline (struct inode*,struct jfs_ea_list*) ; 
 int /*<<< orphan*/  jfs_error (struct super_block*,char*) ; 
 int lengthDXD (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 struct metapage* read_metapage (struct inode*,int,int,int) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 
 int sizeDXD (TYPE_1__*) ; 

__attribute__((used)) static int ea_read(struct inode *ip, struct jfs_ea_list *ealist)
{
	struct super_block *sb = ip->i_sb;
	struct jfs_inode_info *ji = JFS_IP(ip);
	struct jfs_sb_info *sbi = JFS_SBI(sb);
	int nblocks;
	s64 blkno;
	char *cp = (char *) ealist;
	int i;
	int nbytes, nb;
	s32 bytes_to_read;
	struct metapage *mp;

	/* quick check for in-line EA */
	if (ji->ea.flag & DXD_INLINE)
		return ea_read_inline(ip, ealist);

	nbytes = sizeDXD(&ji->ea);
	if (!nbytes) {
		jfs_error(sb, "nbytes is 0\n");
		return -EIO;
	}

	/*
	 * Figure out how many blocks were allocated when this EA list was
	 * originally written to disk.
	 */
	nblocks = lengthDXD(&ji->ea) << sbi->l2nbperpage;
	blkno = addressDXD(&ji->ea) << sbi->l2nbperpage;

	/*
	 * I have found the disk blocks which were originally used to store
	 * the FEALIST.  now i loop over each contiguous block copying the
	 * data into the buffer.
	 */
	for (i = 0; i < nblocks; i += sbi->nbperpage) {
		/*
		 * Determine how many bytes for this request, and round up to
		 * the nearest aggregate block size
		 */
		nb = min(PSIZE, nbytes);
		bytes_to_read =
		    ((((nb + sb->s_blocksize - 1)) >> sb->s_blocksize_bits))
		    << sb->s_blocksize_bits;

		if (!(mp = read_metapage(ip, blkno + i, bytes_to_read, 1)))
			return -EIO;

		memcpy(cp, mp->data, nb);
		release_metapage(mp);

		cp += PSIZE;
		nbytes -= nb;
	}

	return 0;
}