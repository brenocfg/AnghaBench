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
typedef  char u8 ;
typedef  int u32 ;
struct super_block {int s_blocksize_bits; int s_blocksize; int /*<<< orphan*/  s_flags; } ;
struct hfs_mdb {int drSigWord; int drAtrb; int /*<<< orphan*/  drLsMod; int /*<<< orphan*/  drWrCnt; int /*<<< orphan*/  drVBMSt; int /*<<< orphan*/  drDirCnt; int /*<<< orphan*/  drFilCnt; int /*<<< orphan*/  drNmRtDirs; int /*<<< orphan*/  drNmFls; int /*<<< orphan*/  drNxtCNID; int /*<<< orphan*/  drFreeBks; int /*<<< orphan*/  drAlBlSt; int /*<<< orphan*/  drClpSiz; int /*<<< orphan*/  drNmAlBlks; int /*<<< orphan*/  drAlBlkSiz; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int sector_t ;
typedef  int loff_t ;
typedef  int __be16 ;
struct TYPE_2__ {int alloc_blksz; int part_start; int fs_ablocks; int fs_div; int clumpablks; int fs_start; int free_ablocks; int next_id; int root_files; int root_dirs; int file_count; int folder_count; struct buffer_head* mdb_bh; void* cat_tree; void* ext_tree; scalar_t__ bitmap; struct hfs_mdb* alt_mdb; struct buffer_head* alt_mdb_bh; struct hfs_mdb* mdb; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HFS_CAT_CNID ; 
 int /*<<< orphan*/  HFS_EXT_CNID ; 
 int HFS_MDB_BLK ; 
 TYPE_1__* HFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  HFS_SB_ATTRIB_INCNSTNT ; 
 int /*<<< orphan*/  HFS_SB_ATTRIB_SLOCK ; 
 int /*<<< orphan*/  HFS_SB_ATTRIB_UNMNT ; 
 int HFS_SECTOR_SIZE ; 
 int HFS_SECTOR_SIZE_BITS ; 
 int /*<<< orphan*/  HFS_SUPER_MAGIC ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SB_RDONLY ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* hfs_btree_open (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_cat_keycmp ; 
 int /*<<< orphan*/  hfs_ext_keycmp ; 
 scalar_t__ hfs_get_last_session (struct super_block*,int*,int*) ; 
 int /*<<< orphan*/  hfs_mdb_put (struct super_block*) ; 
 int /*<<< orphan*/  hfs_mtime () ; 
 scalar_t__ hfs_part_find (struct super_block*,int*,int*) ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 struct buffer_head* sb_bread (struct super_block*,int) ; 
 struct buffer_head* sb_bread512 (struct super_block*,int,struct hfs_mdb*) ; 
 int sb_min_blocksize (struct super_block*,int) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  sb_set_blocksize (struct super_block*,int) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 

int hfs_mdb_get(struct super_block *sb)
{
	struct buffer_head *bh;
	struct hfs_mdb *mdb, *mdb2;
	unsigned int block;
	char *ptr;
	int off2, len, size, sect;
	sector_t part_start, part_size;
	loff_t off;
	__be16 attrib;

	/* set the device driver to 512-byte blocks */
	size = sb_min_blocksize(sb, HFS_SECTOR_SIZE);
	if (!size)
		return -EINVAL;

	if (hfs_get_last_session(sb, &part_start, &part_size))
		return -EINVAL;
	while (1) {
		/* See if this is an HFS filesystem */
		bh = sb_bread512(sb, part_start + HFS_MDB_BLK, mdb);
		if (!bh)
			goto out;

		if (mdb->drSigWord == cpu_to_be16(HFS_SUPER_MAGIC))
			break;
		brelse(bh);

		/* check for a partition block
		 * (should do this only for cdrom/loop though)
		 */
		if (hfs_part_find(sb, &part_start, &part_size))
			goto out;
	}

	HFS_SB(sb)->alloc_blksz = size = be32_to_cpu(mdb->drAlBlkSiz);
	if (!size || (size & (HFS_SECTOR_SIZE - 1))) {
		pr_err("bad allocation block size %d\n", size);
		goto out_bh;
	}

	size = min(HFS_SB(sb)->alloc_blksz, (u32)PAGE_SIZE);
	/* size must be a multiple of 512 */
	while (size & (size - 1))
		size -= HFS_SECTOR_SIZE;
	sect = be16_to_cpu(mdb->drAlBlSt) + part_start;
	/* align block size to first sector */
	while (sect & ((size - 1) >> HFS_SECTOR_SIZE_BITS))
		size >>= 1;
	/* align block size to weird alloc size */
	while (HFS_SB(sb)->alloc_blksz & (size - 1))
		size >>= 1;
	brelse(bh);
	if (!sb_set_blocksize(sb, size)) {
		pr_err("unable to set blocksize to %u\n", size);
		goto out;
	}

	bh = sb_bread512(sb, part_start + HFS_MDB_BLK, mdb);
	if (!bh)
		goto out;
	if (mdb->drSigWord != cpu_to_be16(HFS_SUPER_MAGIC))
		goto out_bh;

	HFS_SB(sb)->mdb_bh = bh;
	HFS_SB(sb)->mdb = mdb;

	/* These parameters are read from the MDB, and never written */
	HFS_SB(sb)->part_start = part_start;
	HFS_SB(sb)->fs_ablocks = be16_to_cpu(mdb->drNmAlBlks);
	HFS_SB(sb)->fs_div = HFS_SB(sb)->alloc_blksz >> sb->s_blocksize_bits;
	HFS_SB(sb)->clumpablks = be32_to_cpu(mdb->drClpSiz) /
				 HFS_SB(sb)->alloc_blksz;
	if (!HFS_SB(sb)->clumpablks)
		HFS_SB(sb)->clumpablks = 1;
	HFS_SB(sb)->fs_start = (be16_to_cpu(mdb->drAlBlSt) + part_start) >>
			       (sb->s_blocksize_bits - HFS_SECTOR_SIZE_BITS);

	/* These parameters are read from and written to the MDB */
	HFS_SB(sb)->free_ablocks = be16_to_cpu(mdb->drFreeBks);
	HFS_SB(sb)->next_id = be32_to_cpu(mdb->drNxtCNID);
	HFS_SB(sb)->root_files = be16_to_cpu(mdb->drNmFls);
	HFS_SB(sb)->root_dirs = be16_to_cpu(mdb->drNmRtDirs);
	HFS_SB(sb)->file_count = be32_to_cpu(mdb->drFilCnt);
	HFS_SB(sb)->folder_count = be32_to_cpu(mdb->drDirCnt);

	/* TRY to get the alternate (backup) MDB. */
	sect = part_start + part_size - 2;
	bh = sb_bread512(sb, sect, mdb2);
	if (bh) {
		if (mdb2->drSigWord == cpu_to_be16(HFS_SUPER_MAGIC)) {
			HFS_SB(sb)->alt_mdb_bh = bh;
			HFS_SB(sb)->alt_mdb = mdb2;
		} else
			brelse(bh);
	}

	if (!HFS_SB(sb)->alt_mdb) {
		pr_warn("unable to locate alternate MDB\n");
		pr_warn("continuing without an alternate MDB\n");
	}

	HFS_SB(sb)->bitmap = kmalloc(8192, GFP_KERNEL);
	if (!HFS_SB(sb)->bitmap)
		goto out;

	/* read in the bitmap */
	block = be16_to_cpu(mdb->drVBMSt) + part_start;
	off = (loff_t)block << HFS_SECTOR_SIZE_BITS;
	size = (HFS_SB(sb)->fs_ablocks + 8) / 8;
	ptr = (u8 *)HFS_SB(sb)->bitmap;
	while (size) {
		bh = sb_bread(sb, off >> sb->s_blocksize_bits);
		if (!bh) {
			pr_err("unable to read volume bitmap\n");
			goto out;
		}
		off2 = off & (sb->s_blocksize - 1);
		len = min((int)sb->s_blocksize - off2, size);
		memcpy(ptr, bh->b_data + off2, len);
		brelse(bh);
		ptr += len;
		off += len;
		size -= len;
	}

	HFS_SB(sb)->ext_tree = hfs_btree_open(sb, HFS_EXT_CNID, hfs_ext_keycmp);
	if (!HFS_SB(sb)->ext_tree) {
		pr_err("unable to open extent tree\n");
		goto out;
	}
	HFS_SB(sb)->cat_tree = hfs_btree_open(sb, HFS_CAT_CNID, hfs_cat_keycmp);
	if (!HFS_SB(sb)->cat_tree) {
		pr_err("unable to open catalog tree\n");
		goto out;
	}

	attrib = mdb->drAtrb;
	if (!(attrib & cpu_to_be16(HFS_SB_ATTRIB_UNMNT))) {
		pr_warn("filesystem was not cleanly unmounted, running fsck.hfs is recommended.  mounting read-only.\n");
		sb->s_flags |= SB_RDONLY;
	}
	if ((attrib & cpu_to_be16(HFS_SB_ATTRIB_SLOCK))) {
		pr_warn("filesystem is marked locked, mounting read-only.\n");
		sb->s_flags |= SB_RDONLY;
	}
	if (!sb_rdonly(sb)) {
		/* Mark the volume uncleanly unmounted in case we crash */
		attrib &= cpu_to_be16(~HFS_SB_ATTRIB_UNMNT);
		attrib |= cpu_to_be16(HFS_SB_ATTRIB_INCNSTNT);
		mdb->drAtrb = attrib;
		be32_add_cpu(&mdb->drWrCnt, 1);
		mdb->drLsMod = hfs_mtime();

		mark_buffer_dirty(HFS_SB(sb)->mdb_bh);
		sync_dirty_buffer(HFS_SB(sb)->mdb_bh);
	}

	return 0;

out_bh:
	brelse(bh);
out:
	hfs_mdb_put(sb);
	return -EIO;
}