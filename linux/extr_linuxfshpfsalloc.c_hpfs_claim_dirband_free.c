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
struct hpfs_sb_info {unsigned int sb_n_free_dnodes; int sb_dirband_size; } ;
typedef  int /*<<< orphan*/  secno ;

/* Variables and functions */
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,int /*<<< orphan*/ ) ; 
 struct hpfs_sb_info* hpfs_sb (struct super_block*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void hpfs_claim_dirband_free(struct super_block *s, secno sec)
{
	struct hpfs_sb_info *sbi = hpfs_sb(s);
	if (sbi->sb_n_free_dnodes != (unsigned)-1) {
		if (unlikely(sbi->sb_n_free_dnodes >= sbi->sb_dirband_size / 4)) {
			hpfs_error(s, "dirband free count overflow, freeing sector %08x", sec);
			sbi->sb_n_free_dnodes = -1;
			return;
		}
		sbi->sb_n_free_dnodes++;
	}
}