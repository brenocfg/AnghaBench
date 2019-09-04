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
typedef  int uint64_t ;
struct super_block {struct exofs_sb_info* s_fs_info; } ;
struct osd_attr {int /*<<< orphan*/  val_ptr; } ;
struct ore_io_state {int /*<<< orphan*/  in_attr_len; struct osd_attr* in_attr; } ;
struct kstatfs {int f_blocks; int f_bfree; int f_bavail; int /*<<< orphan*/  f_namelen; scalar_t__ f_ffree; scalar_t__ f_files; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct exofs_sb_info {scalar_t__ s_numfiles; int /*<<< orphan*/  oc; int /*<<< orphan*/  layout; } ;
struct dentry {struct super_block* d_sb; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct osd_attr*) ; 
 struct osd_attr ATTR_DEF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EXOFS_BLKSIZE ; 
 int /*<<< orphan*/  EXOFS_DBGMSG (char*) ; 
 scalar_t__ EXOFS_MAX_ID ; 
 int /*<<< orphan*/  EXOFS_NAME_LEN ; 
 int /*<<< orphan*/  EXOFS_SUPER_MAGIC ; 
 int /*<<< orphan*/  OSD_APAGE_PARTITION_INFORMATION ; 
 int /*<<< orphan*/  OSD_APAGE_PARTITION_QUOTAS ; 
 int /*<<< orphan*/  OSD_ATTR_PI_USED_CAPACITY ; 
 int /*<<< orphan*/  OSD_ATTR_PQ_CAPACITY_QUOTA ; 
 int ULLONG_MAX ; 
 int extract_attr_from_ios (struct ore_io_state*,struct osd_attr*) ; 
 int get_unaligned_be64 (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int ore_get_io_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ore_io_state**) ; 
 int /*<<< orphan*/  ore_put_io_state (struct ore_io_state*) ; 
 int ore_read (struct ore_io_state*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int exofs_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *sb = dentry->d_sb;
	struct exofs_sb_info *sbi = sb->s_fs_info;
	struct ore_io_state *ios;
	struct osd_attr attrs[] = {
		ATTR_DEF(OSD_APAGE_PARTITION_QUOTAS,
			OSD_ATTR_PQ_CAPACITY_QUOTA, sizeof(__be64)),
		ATTR_DEF(OSD_APAGE_PARTITION_INFORMATION,
			OSD_ATTR_PI_USED_CAPACITY, sizeof(__be64)),
	};
	uint64_t capacity = ULLONG_MAX;
	uint64_t used = ULLONG_MAX;
	int ret;

	ret = ore_get_io_state(&sbi->layout, &sbi->oc, &ios);
	if (ret) {
		EXOFS_DBGMSG("ore_get_io_state failed.\n");
		return ret;
	}

	ios->in_attr = attrs;
	ios->in_attr_len = ARRAY_SIZE(attrs);

	ret = ore_read(ios);
	if (unlikely(ret))
		goto out;

	ret = extract_attr_from_ios(ios, &attrs[0]);
	if (likely(!ret)) {
		capacity = get_unaligned_be64(attrs[0].val_ptr);
		if (unlikely(!capacity))
			capacity = ULLONG_MAX;
	} else
		EXOFS_DBGMSG("exofs_statfs: get capacity failed.\n");

	ret = extract_attr_from_ios(ios, &attrs[1]);
	if (likely(!ret))
		used = get_unaligned_be64(attrs[1].val_ptr);
	else
		EXOFS_DBGMSG("exofs_statfs: get used-space failed.\n");

	/* fill in the stats buffer */
	buf->f_type = EXOFS_SUPER_MAGIC;
	buf->f_bsize = EXOFS_BLKSIZE;
	buf->f_blocks = capacity >> 9;
	buf->f_bfree = (capacity - used) >> 9;
	buf->f_bavail = buf->f_bfree;
	buf->f_files = sbi->s_numfiles;
	buf->f_ffree = EXOFS_MAX_ID - sbi->s_numfiles;
	buf->f_namelen = EXOFS_NAME_LEN;

out:
	ore_put_io_state(ios);
	return ret;
}