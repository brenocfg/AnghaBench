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
struct sysv_sb_info {int /*<<< orphan*/  s_type; int /*<<< orphan*/  s_bytesex; } ;
struct coh_super_block {int /*<<< orphan*/  s_fpack; int /*<<< orphan*/  s_fname; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int BLOCK_SIZE ; 
 int /*<<< orphan*/  BYTESEX_PDP ; 
 int /*<<< orphan*/  FSTYPE_COH ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int detect_coherent(struct sysv_sb_info *sbi, struct buffer_head *bh)
{
	struct coh_super_block * sbd;

	sbd = (struct coh_super_block *) (bh->b_data + BLOCK_SIZE/2);
	if ((memcmp(sbd->s_fname,"noname",6) && memcmp(sbd->s_fname,"xxxxx ",6))
	    || (memcmp(sbd->s_fpack,"nopack",6) && memcmp(sbd->s_fpack,"xxxxx\n",6)))
		return 0;
	sbi->s_bytesex = BYTESEX_PDP;
	sbi->s_type = FSTYPE_COH;
	return 1;
}