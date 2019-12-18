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
struct rsvd_count {int first_do_lblk_found; int partial; scalar_t__ lclu; scalar_t__ ndelonly; scalar_t__ last_do_lblk; scalar_t__ first_do_lblk; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct extent_status {scalar_t__ es_lblk; } ;
struct ext4_sb_info {int s_cluster_ratio; scalar_t__ s_cluster_bits; } ;
typedef  scalar_t__ ext4_lblk_t ;

/* Variables and functions */
 scalar_t__ EXT4_B2C (struct ext4_sb_info*,scalar_t__) ; 
 scalar_t__ EXT4_LBLK_CFILL (struct ext4_sb_info*,scalar_t__) ; 
 scalar_t__ EXT4_LBLK_COFF (struct ext4_sb_info*,scalar_t__) ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ ext4_es_end (struct extent_status*) ; 
 int /*<<< orphan*/  ext4_es_is_delonly (struct extent_status*) ; 

__attribute__((used)) static void count_rsvd(struct inode *inode, ext4_lblk_t lblk, long len,
		       struct extent_status *es, struct rsvd_count *rc)
{
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	ext4_lblk_t i, end, nclu;

	if (!ext4_es_is_delonly(es))
		return;

	WARN_ON(len <= 0);

	if (sbi->s_cluster_ratio == 1) {
		rc->ndelonly += (int) len;
		return;
	}

	/* bigalloc */

	i = (lblk < es->es_lblk) ? es->es_lblk : lblk;
	end = lblk + (ext4_lblk_t) len - 1;
	end = (end > ext4_es_end(es)) ? ext4_es_end(es) : end;

	/* record the first block of the first delonly extent seen */
	if (rc->first_do_lblk_found == false) {
		rc->first_do_lblk = i;
		rc->first_do_lblk_found = true;
	}

	/* update the last lblk in the region seen so far */
	rc->last_do_lblk = end;

	/*
	 * if we're tracking a partial cluster and the current extent
	 * doesn't start with it, count it and stop tracking
	 */
	if (rc->partial && (rc->lclu != EXT4_B2C(sbi, i))) {
		rc->ndelonly++;
		rc->partial = false;
	}

	/*
	 * if the first cluster doesn't start on a cluster boundary but
	 * ends on one, count it
	 */
	if (EXT4_LBLK_COFF(sbi, i) != 0) {
		if (end >= EXT4_LBLK_CFILL(sbi, i)) {
			rc->ndelonly++;
			rc->partial = false;
			i = EXT4_LBLK_CFILL(sbi, i) + 1;
		}
	}

	/*
	 * if the current cluster starts on a cluster boundary, count the
	 * number of whole delonly clusters in the extent
	 */
	if ((i + sbi->s_cluster_ratio - 1) <= end) {
		nclu = (end - i + 1) >> sbi->s_cluster_bits;
		rc->ndelonly += nclu;
		i += nclu << sbi->s_cluster_bits;
	}

	/*
	 * start tracking a partial cluster if there's a partial at the end
	 * of the current extent and we're not already tracking one
	 */
	if (!rc->partial && i <= end) {
		rc->partial = true;
		rc->lclu = EXT4_B2C(sbi, i);
	}
}