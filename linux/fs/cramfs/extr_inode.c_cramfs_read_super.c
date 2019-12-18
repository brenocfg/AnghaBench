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
struct super_block {int dummy; } ;
struct fs_context {int sb_flags; } ;
struct TYPE_4__ {scalar_t__ files; scalar_t__ blocks; } ;
struct TYPE_3__ {int mode; int offset; } ;
struct cramfs_super {scalar_t__ magic; int flags; int size; TYPE_2__ fsid; TYPE_1__ root; } ;
struct cramfs_sb_info {int size; scalar_t__ magic; int flags; scalar_t__ files; scalar_t__ blocks; } ;

/* Variables and functions */
 int CRAMFS_FLAG_FSID_VERSION_2 ; 
 int CRAMFS_FLAG_SHIFTED_ROOT_OFFSET ; 
 scalar_t__ CRAMFS_MAGIC ; 
 scalar_t__ CRAMFS_MAGIC_WEND ; 
 struct cramfs_sb_info* CRAMFS_SB (struct super_block*) ; 
 int CRAMFS_SUPPORTED_FLAGS ; 
 int EINVAL ; 
 int PAGE_SIZE ; 
 int SB_SILENT ; 
 int /*<<< orphan*/  S_ISDIR (int) ; 
 int /*<<< orphan*/  cramfs_read (struct super_block*,int,int) ; 
 int /*<<< orphan*/  errorf (struct fs_context*,char*,...) ; 
 int /*<<< orphan*/  infof (struct fs_context*,char*) ; 
 int /*<<< orphan*/  memcpy (struct cramfs_super*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_mutex ; 

__attribute__((used)) static int cramfs_read_super(struct super_block *sb, struct fs_context *fc,
			     struct cramfs_super *super)
{
	struct cramfs_sb_info *sbi = CRAMFS_SB(sb);
	unsigned long root_offset;
	bool silent = fc->sb_flags & SB_SILENT;

	/* We don't know the real size yet */
	sbi->size = PAGE_SIZE;

	/* Read the first block and get the superblock from it */
	mutex_lock(&read_mutex);
	memcpy(super, cramfs_read(sb, 0, sizeof(*super)), sizeof(*super));
	mutex_unlock(&read_mutex);

	/* Do sanity checks on the superblock */
	if (super->magic != CRAMFS_MAGIC) {
		/* check for wrong endianness */
		if (super->magic == CRAMFS_MAGIC_WEND) {
			if (!silent)
				errorf(fc, "cramfs: wrong endianness");
			return -EINVAL;
		}

		/* check at 512 byte offset */
		mutex_lock(&read_mutex);
		memcpy(super,
		       cramfs_read(sb, 512, sizeof(*super)),
		       sizeof(*super));
		mutex_unlock(&read_mutex);
		if (super->magic != CRAMFS_MAGIC) {
			if (super->magic == CRAMFS_MAGIC_WEND && !silent)
				errorf(fc, "cramfs: wrong endianness");
			else if (!silent)
				errorf(fc, "cramfs: wrong magic");
			return -EINVAL;
		}
	}

	/* get feature flags first */
	if (super->flags & ~CRAMFS_SUPPORTED_FLAGS) {
		errorf(fc, "cramfs: unsupported filesystem features");
		return -EINVAL;
	}

	/* Check that the root inode is in a sane state */
	if (!S_ISDIR(super->root.mode)) {
		errorf(fc, "cramfs: root is not a directory");
		return -EINVAL;
	}
	/* correct strange, hard-coded permissions of mkcramfs */
	super->root.mode |= 0555;

	root_offset = super->root.offset << 2;
	if (super->flags & CRAMFS_FLAG_FSID_VERSION_2) {
		sbi->size = super->size;
		sbi->blocks = super->fsid.blocks;
		sbi->files = super->fsid.files;
	} else {
		sbi->size = 1<<28;
		sbi->blocks = 0;
		sbi->files = 0;
	}
	sbi->magic = super->magic;
	sbi->flags = super->flags;
	if (root_offset == 0)
		infof(fc, "cramfs: empty filesystem");
	else if (!(super->flags & CRAMFS_FLAG_SHIFTED_ROOT_OFFSET) &&
		 ((root_offset != sizeof(struct cramfs_super)) &&
		  (root_offset != 512 + sizeof(struct cramfs_super))))
	{
		errorf(fc, "cramfs: bad root offset %lu", root_offset);
		return -EINVAL;
	}

	return 0;
}