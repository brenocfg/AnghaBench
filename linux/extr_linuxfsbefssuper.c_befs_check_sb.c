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
struct super_block {int dummy; } ;
struct befs_sb_info {scalar_t__ magic1; scalar_t__ magic2; scalar_t__ magic3; int block_size; int block_shift; int ag_shift; int blocks_per_ag; scalar_t__ log_start; scalar_t__ log_end; scalar_t__ flags; } ;

/* Variables and functions */
 scalar_t__ BEFS_DIRTY ; 
 int BEFS_ERR ; 
 int BEFS_OK ; 
 struct befs_sb_info* BEFS_SB (struct super_block*) ; 
 scalar_t__ BEFS_SUPER_MAGIC1 ; 
 scalar_t__ BEFS_SUPER_MAGIC2 ; 
 scalar_t__ BEFS_SUPER_MAGIC3 ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  befs_error (struct super_block*,char*,...) ; 

int
befs_check_sb(struct super_block *sb)
{
	struct befs_sb_info *befs_sb = BEFS_SB(sb);

	/* Check magic headers of super block */
	if ((befs_sb->magic1 != BEFS_SUPER_MAGIC1)
	    || (befs_sb->magic2 != BEFS_SUPER_MAGIC2)
	    || (befs_sb->magic3 != BEFS_SUPER_MAGIC3)) {
		befs_error(sb, "invalid magic header");
		return BEFS_ERR;
	}

	/*
	 * Check blocksize of BEFS.
	 *
	 * Blocksize of BEFS is 1024, 2048, 4096 or 8192.
	 */

	if ((befs_sb->block_size != 1024)
	    && (befs_sb->block_size != 2048)
	    && (befs_sb->block_size != 4096)
	    && (befs_sb->block_size != 8192)) {
		befs_error(sb, "invalid blocksize: %u", befs_sb->block_size);
		return BEFS_ERR;
	}

	if (befs_sb->block_size > PAGE_SIZE) {
		befs_error(sb, "blocksize(%u) cannot be larger "
			   "than system pagesize(%lu)", befs_sb->block_size,
			   PAGE_SIZE);
		return BEFS_ERR;
	}

	/*
	 * block_shift and block_size encode the same information
	 * in different ways as a consistency check.
	 */

	if ((1 << befs_sb->block_shift) != befs_sb->block_size) {
		befs_error(sb, "block_shift disagrees with block_size. "
			   "Corruption likely.");
		return BEFS_ERR;
	}


	/* ag_shift also encodes the same information as blocks_per_ag in a
	 * different way, non-fatal consistency check
	 */
	if ((1 << befs_sb->ag_shift) != befs_sb->blocks_per_ag)
		befs_error(sb, "ag_shift disagrees with blocks_per_ag.");

	if (befs_sb->log_start != befs_sb->log_end ||
	    befs_sb->flags == BEFS_DIRTY) {
		befs_error(sb, "Filesystem not clean! There are blocks in the "
			   "journal. You must boot into BeOS and mount this "
			   "volume to make it clean.");
		return BEFS_ERR;
	}

	return BEFS_OK;
}