#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_bdev; } ;
struct ext4_super_block {int /*<<< orphan*/  s_journal_dev; int /*<<< orphan*/  s_journal_inum; } ;
struct TYPE_8__ {int j_flags; } ;
typedef  TYPE_1__ journal_t ;
typedef  scalar_t__ dev_t ;
struct TYPE_9__ {TYPE_1__* s_journal; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int EROFS ; 
 TYPE_7__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_S_ERR_LEN ; 
 int EXT4_S_ERR_START ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int JBD2_BARRIER ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int bdev_read_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned long) ; 
 int /*<<< orphan*/  ext4_clear_journal_err (struct super_block*,struct ext4_super_block*) ; 
 int /*<<< orphan*/  ext4_commit_super (struct super_block*,int) ; 
 TYPE_1__* ext4_get_dev_journal (struct super_block*,scalar_t__) ; 
 TYPE_1__* ext4_get_journal (struct super_block*,unsigned int) ; 
 int /*<<< orphan*/  ext4_has_feature_journal (struct super_block*) ; 
 scalar_t__ ext4_has_feature_journal_needs_recovery (struct super_block*) ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jbd2_journal_destroy (TYPE_1__*) ; 
 int jbd2_journal_load (TYPE_1__*) ; 
 int jbd2_journal_wipe (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ new_decode_dev (unsigned long) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 

__attribute__((used)) static int ext4_load_journal(struct super_block *sb,
			     struct ext4_super_block *es,
			     unsigned long journal_devnum)
{
	journal_t *journal;
	unsigned int journal_inum = le32_to_cpu(es->s_journal_inum);
	dev_t journal_dev;
	int err = 0;
	int really_read_only;

	BUG_ON(!ext4_has_feature_journal(sb));

	if (journal_devnum &&
	    journal_devnum != le32_to_cpu(es->s_journal_dev)) {
		ext4_msg(sb, KERN_INFO, "external journal device major/minor "
			"numbers have changed");
		journal_dev = new_decode_dev(journal_devnum);
	} else
		journal_dev = new_decode_dev(le32_to_cpu(es->s_journal_dev));

	really_read_only = bdev_read_only(sb->s_bdev);

	/*
	 * Are we loading a blank journal or performing recovery after a
	 * crash?  For recovery, we need to check in advance whether we
	 * can get read-write access to the device.
	 */
	if (ext4_has_feature_journal_needs_recovery(sb)) {
		if (sb_rdonly(sb)) {
			ext4_msg(sb, KERN_INFO, "INFO: recovery "
					"required on readonly filesystem");
			if (really_read_only) {
				ext4_msg(sb, KERN_ERR, "write access "
					"unavailable, cannot proceed "
					"(try mounting with noload)");
				return -EROFS;
			}
			ext4_msg(sb, KERN_INFO, "write access will "
			       "be enabled during recovery");
		}
	}

	if (journal_inum && journal_dev) {
		ext4_msg(sb, KERN_ERR, "filesystem has both journal "
		       "and inode journals!");
		return -EINVAL;
	}

	if (journal_inum) {
		if (!(journal = ext4_get_journal(sb, journal_inum)))
			return -EINVAL;
	} else {
		if (!(journal = ext4_get_dev_journal(sb, journal_dev)))
			return -EINVAL;
	}

	if (!(journal->j_flags & JBD2_BARRIER))
		ext4_msg(sb, KERN_INFO, "barriers disabled");

	if (!ext4_has_feature_journal_needs_recovery(sb))
		err = jbd2_journal_wipe(journal, !really_read_only);
	if (!err) {
		char *save = kmalloc(EXT4_S_ERR_LEN, GFP_KERNEL);
		if (save)
			memcpy(save, ((char *) es) +
			       EXT4_S_ERR_START, EXT4_S_ERR_LEN);
		err = jbd2_journal_load(journal);
		if (save)
			memcpy(((char *) es) + EXT4_S_ERR_START,
			       save, EXT4_S_ERR_LEN);
		kfree(save);
	}

	if (err) {
		ext4_msg(sb, KERN_ERR, "error loading journal");
		jbd2_journal_destroy(journal);
		return err;
	}

	EXT4_SB(sb)->s_journal = journal;
	ext4_clear_journal_err(sb, es);

	if (!really_read_only && journal_devnum &&
	    journal_devnum != le32_to_cpu(es->s_journal_dev)) {
		es->s_journal_dev = cpu_to_le32(journal_devnum);

		/* Make sure we flush the recovery flag to disk. */
		ext4_commit_super(sb, 1);
	}

	return 0;
}