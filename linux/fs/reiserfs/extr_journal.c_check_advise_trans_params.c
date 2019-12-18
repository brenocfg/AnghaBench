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
struct super_block {int s_blocksize; } ;
struct reiserfs_journal {int j_trans_max; int j_max_batch; int /*<<< orphan*/  j_max_commit_age; } ;

/* Variables and functions */
 int JOURNAL_MAX_BATCH_DEFAULT ; 
 int /*<<< orphan*/  JOURNAL_MAX_COMMIT_AGE ; 
 int JOURNAL_MIN_RATIO ; 
 int JOURNAL_TRANS_MAX_DEFAULT ; 
 int JOURNAL_TRANS_MIN_DEFAULT ; 
 int REISERFS_STANDARD_BLKSIZE ; 
 int SB_ONDISK_JOURNAL_SIZE (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*,int) ; 

__attribute__((used)) static int check_advise_trans_params(struct super_block *sb,
				     struct reiserfs_journal *journal)
{
        if (journal->j_trans_max) {
		/* Non-default journal params.  Do sanity check for them. */
	        int ratio = 1;
		if (sb->s_blocksize < REISERFS_STANDARD_BLKSIZE)
		        ratio = REISERFS_STANDARD_BLKSIZE / sb->s_blocksize;

		if (journal->j_trans_max > JOURNAL_TRANS_MAX_DEFAULT / ratio ||
		    journal->j_trans_max < JOURNAL_TRANS_MIN_DEFAULT / ratio ||
		    SB_ONDISK_JOURNAL_SIZE(sb) / journal->j_trans_max <
		    JOURNAL_MIN_RATIO) {
			reiserfs_warning(sb, "sh-462",
					 "bad transaction max size (%u). "
					 "FSCK?", journal->j_trans_max);
			return 1;
		}
		if (journal->j_max_batch != (journal->j_trans_max) *
		        JOURNAL_MAX_BATCH_DEFAULT/JOURNAL_TRANS_MAX_DEFAULT) {
			reiserfs_warning(sb, "sh-463",
					 "bad transaction max batch (%u). "
					 "FSCK?", journal->j_max_batch);
			return 1;
		}
	} else {
		/*
		 * Default journal params.
		 * The file system was created by old version
		 * of mkreiserfs, so some fields contain zeros,
		 * and we need to advise proper values for them
		 */
		if (sb->s_blocksize != REISERFS_STANDARD_BLKSIZE) {
			reiserfs_warning(sb, "sh-464", "bad blocksize (%u)",
					 sb->s_blocksize);
			return 1;
		}
		journal->j_trans_max = JOURNAL_TRANS_MAX_DEFAULT;
		journal->j_max_batch = JOURNAL_MAX_BATCH_DEFAULT;
		journal->j_max_commit_age = JOURNAL_MAX_COMMIT_AGE;
	}
	return 0;
}