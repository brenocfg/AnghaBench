#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct super_block {int s_flags; int s_blocksize; int /*<<< orphan*/ * s_export_op; int /*<<< orphan*/  s_root; int /*<<< orphan*/ * s_d_op; int /*<<< orphan*/  s_id; TYPE_2__* s_bdev; struct affs_sb_info* s_fs_info; scalar_t__ s_time_min; scalar_t__ s_time_max; int /*<<< orphan*/  s_time_gran; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
struct affs_sb_info {unsigned long s_flags; int s_mode; int s_reserved; int s_root_block; int s_partition_size; int s_hashsize; int s_data_blksize; struct buffer_head* s_root_bh; int /*<<< orphan*/  s_gid; int /*<<< orphan*/  s_uid; int /*<<< orphan*/  s_volume; int /*<<< orphan*/  s_prefix; int /*<<< orphan*/  sb_work; int /*<<< orphan*/  work_lock; int /*<<< orphan*/  symlink_lock; int /*<<< orphan*/  s_bmlock; struct super_block* sb; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_10__ {int /*<<< orphan*/  ptype; } ;
struct TYPE_9__ {int* disk_name; int /*<<< orphan*/  stype; } ;
struct TYPE_8__ {unsigned long s_flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  bd_inode; } ;
struct TYPE_6__ {int tz_minuteswest; } ;

/* Variables and functions */
 scalar_t__ AFFS_EPOCH_DELTA ; 
 TYPE_5__* AFFS_ROOT_HEAD (struct buffer_head*) ; 
 TYPE_4__* AFFS_ROOT_TAIL (struct super_block*,struct buffer_head*) ; 
 TYPE_3__* AFFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  AFFS_SUPER_MAGIC ; 
 int EINVAL ; 
 int ENOMEM ; 
#define  FS_DCFFS 140 
#define  FS_DCOFS 139 
#define  FS_FFS 138 
#define  FS_INTLFFS 137 
#define  FS_INTLOFS 136 
#define  FS_OFS 135 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
#define  MUFS_DCFFS 134 
#define  MUFS_DCOFS 133 
#define  MUFS_FFS 132 
#define  MUFS_FS 131 
#define  MUFS_INTLFFS 130 
#define  MUFS_INTLOFS 129 
#define  MUFS_OFS 128 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct inode*) ; 
 int SB_NODEV ; 
 int SB_NODIRATIME ; 
 int SB_NOEXEC ; 
 int SB_NOSUID ; 
 int SB_RDONLY ; 
 int /*<<< orphan*/  SF_INTL ; 
 int /*<<< orphan*/  SF_MUFS ; 
 int /*<<< orphan*/  SF_OFS ; 
 int /*<<< orphan*/  SF_VERBOSE ; 
 scalar_t__ ST_ROOT ; 
 scalar_t__ T_SHORT ; 
 long long U32_MAX ; 
 struct buffer_head* affs_bread (struct super_block*,int) ; 
 int /*<<< orphan*/  affs_brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  affs_checksum_block (struct super_block*,struct buffer_head*) ; 
 int /*<<< orphan*/  affs_dentry_operations ; 
 int /*<<< orphan*/  affs_export_ops ; 
 struct inode* affs_iget (struct super_block*,int) ; 
 int affs_init_bitmap (struct super_block*,int*) ; 
 int /*<<< orphan*/  affs_intl_dentry_operations ; 
 int /*<<< orphan*/  affs_set_blocksize (struct super_block*,int) ; 
 int /*<<< orphan*/  affs_set_opt (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affs_sops ; 
 scalar_t__ affs_test_opt (unsigned long,int /*<<< orphan*/ ) ; 
 int bdev_logical_block_size (TYPE_2__*) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 int /*<<< orphan*/  flush_superblock ; 
 int i_size_read (int /*<<< orphan*/ ) ; 
 struct affs_sb_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_options (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_notice (char*,int,...) ; 
 struct buffer_head* sb_bread (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ sys_tz ; 

__attribute__((used)) static int affs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct affs_sb_info	*sbi;
	struct buffer_head	*root_bh = NULL;
	struct buffer_head	*boot_bh;
	struct inode		*root_inode = NULL;
	s32			 root_block;
	int			 size, blocksize;
	u32			 chksum;
	int			 num_bm;
	int			 i, j;
	kuid_t			 uid;
	kgid_t			 gid;
	int			 reserved;
	unsigned long		 mount_flags;
	int			 tmp_flags;	/* fix remount prototype... */
	u8			 sig[4];
	int			 ret;

	pr_debug("read_super(%s)\n", data ? (const char *)data : "no options");

	sb->s_magic             = AFFS_SUPER_MAGIC;
	sb->s_op                = &affs_sops;
	sb->s_flags |= SB_NODIRATIME;

	sb->s_time_gran = NSEC_PER_SEC;
	sb->s_time_min = sys_tz.tz_minuteswest * 60 + AFFS_EPOCH_DELTA;
	sb->s_time_max = 86400LL * U32_MAX + 86400 + sb->s_time_min;

	sbi = kzalloc(sizeof(struct affs_sb_info), GFP_KERNEL);
	if (!sbi)
		return -ENOMEM;

	sb->s_fs_info = sbi;
	sbi->sb = sb;
	mutex_init(&sbi->s_bmlock);
	spin_lock_init(&sbi->symlink_lock);
	spin_lock_init(&sbi->work_lock);
	INIT_DELAYED_WORK(&sbi->sb_work, flush_superblock);

	if (!parse_options(data,&uid,&gid,&i,&reserved,&root_block,
				&blocksize,&sbi->s_prefix,
				sbi->s_volume, &mount_flags)) {
		pr_err("Error parsing options\n");
		return -EINVAL;
	}
	/* N.B. after this point s_prefix must be released */

	sbi->s_flags   = mount_flags;
	sbi->s_mode    = i;
	sbi->s_uid     = uid;
	sbi->s_gid     = gid;
	sbi->s_reserved= reserved;

	/* Get the size of the device in 512-byte blocks.
	 * If we later see that the partition uses bigger
	 * blocks, we will have to change it.
	 */

	size = i_size_read(sb->s_bdev->bd_inode) >> 9;
	pr_debug("initial blocksize=%d, #blocks=%d\n", 512, size);

	affs_set_blocksize(sb, PAGE_SIZE);
	/* Try to find root block. Its location depends on the block size. */

	i = bdev_logical_block_size(sb->s_bdev);
	j = PAGE_SIZE;
	if (blocksize > 0) {
		i = j = blocksize;
		size = size / (blocksize / 512);
	}

	for (blocksize = i; blocksize <= j; blocksize <<= 1, size >>= 1) {
		sbi->s_root_block = root_block;
		if (root_block < 0)
			sbi->s_root_block = (reserved + size - 1) / 2;
		pr_debug("setting blocksize to %d\n", blocksize);
		affs_set_blocksize(sb, blocksize);
		sbi->s_partition_size = size;

		/* The root block location that was calculated above is not
		 * correct if the partition size is an odd number of 512-
		 * byte blocks, which will be rounded down to a number of
		 * 1024-byte blocks, and if there were an even number of
		 * reserved blocks. Ideally, all partition checkers should
		 * report the real number of blocks of the real blocksize,
		 * but since this just cannot be done, we have to try to
		 * find the root block anyways. In the above case, it is one
		 * block behind the calculated one. So we check this one, too.
		 */
		for (num_bm = 0; num_bm < 2; num_bm++) {
			pr_debug("Dev %s, trying root=%u, bs=%d, "
				"size=%d, reserved=%d\n",
				sb->s_id,
				sbi->s_root_block + num_bm,
				blocksize, size, reserved);
			root_bh = affs_bread(sb, sbi->s_root_block + num_bm);
			if (!root_bh)
				continue;
			if (!affs_checksum_block(sb, root_bh) &&
			    be32_to_cpu(AFFS_ROOT_HEAD(root_bh)->ptype) == T_SHORT &&
			    be32_to_cpu(AFFS_ROOT_TAIL(sb, root_bh)->stype) == ST_ROOT) {
				sbi->s_hashsize    = blocksize / 4 - 56;
				sbi->s_root_block += num_bm;
				goto got_root;
			}
			affs_brelse(root_bh);
			root_bh = NULL;
		}
	}
	if (!silent)
		pr_err("No valid root block on device %s\n", sb->s_id);
	return -EINVAL;

	/* N.B. after this point bh must be released */
got_root:
	/* Keep super block in cache */
	sbi->s_root_bh = root_bh;
	root_block = sbi->s_root_block;

	/* Find out which kind of FS we have */
	boot_bh = sb_bread(sb, 0);
	if (!boot_bh) {
		pr_err("Cannot read boot block\n");
		return -EINVAL;
	}
	memcpy(sig, boot_bh->b_data, 4);
	brelse(boot_bh);
	chksum = be32_to_cpu(*(__be32 *)sig);

	/* Dircache filesystems are compatible with non-dircache ones
	 * when reading. As long as they aren't supported, writing is
	 * not recommended.
	 */
	if ((chksum == FS_DCFFS || chksum == MUFS_DCFFS || chksum == FS_DCOFS
	     || chksum == MUFS_DCOFS) && !sb_rdonly(sb)) {
		pr_notice("Dircache FS - mounting %s read only\n", sb->s_id);
		sb->s_flags |= SB_RDONLY;
	}
	switch (chksum) {
	case MUFS_FS:
	case MUFS_INTLFFS:
	case MUFS_DCFFS:
		affs_set_opt(sbi->s_flags, SF_MUFS);
		/* fall thru */
	case FS_INTLFFS:
	case FS_DCFFS:
		affs_set_opt(sbi->s_flags, SF_INTL);
		break;
	case MUFS_FFS:
		affs_set_opt(sbi->s_flags, SF_MUFS);
		break;
	case FS_FFS:
		break;
	case MUFS_OFS:
		affs_set_opt(sbi->s_flags, SF_MUFS);
		/* fall through */
	case FS_OFS:
		affs_set_opt(sbi->s_flags, SF_OFS);
		sb->s_flags |= SB_NOEXEC;
		break;
	case MUFS_DCOFS:
	case MUFS_INTLOFS:
		affs_set_opt(sbi->s_flags, SF_MUFS);
		/* fall through */
	case FS_DCOFS:
	case FS_INTLOFS:
		affs_set_opt(sbi->s_flags, SF_INTL);
		affs_set_opt(sbi->s_flags, SF_OFS);
		sb->s_flags |= SB_NOEXEC;
		break;
	default:
		pr_err("Unknown filesystem on device %s: %08X\n",
		       sb->s_id, chksum);
		return -EINVAL;
	}

	if (affs_test_opt(mount_flags, SF_VERBOSE)) {
		u8 len = AFFS_ROOT_TAIL(sb, root_bh)->disk_name[0];
		pr_notice("Mounting volume \"%.*s\": Type=%.3s\\%c, Blocksize=%d\n",
			len > 31 ? 31 : len,
			AFFS_ROOT_TAIL(sb, root_bh)->disk_name + 1,
			sig, sig[3] + '0', blocksize);
	}

	sb->s_flags |= SB_NODEV | SB_NOSUID;

	sbi->s_data_blksize = sb->s_blocksize;
	if (affs_test_opt(sbi->s_flags, SF_OFS))
		sbi->s_data_blksize -= 24;

	tmp_flags = sb->s_flags;
	ret = affs_init_bitmap(sb, &tmp_flags);
	if (ret)
		return ret;
	sb->s_flags = tmp_flags;

	/* set up enough so that it can read an inode */

	root_inode = affs_iget(sb, root_block);
	if (IS_ERR(root_inode))
		return PTR_ERR(root_inode);

	if (affs_test_opt(AFFS_SB(sb)->s_flags, SF_INTL))
		sb->s_d_op = &affs_intl_dentry_operations;
	else
		sb->s_d_op = &affs_dentry_operations;

	sb->s_root = d_make_root(root_inode);
	if (!sb->s_root) {
		pr_err("AFFS: Get root inode failed\n");
		return -ENOMEM;
	}

	sb->s_export_op = &affs_export_ops;
	pr_debug("s_flags=%lX\n", sb->s_flags);
	return 0;
}