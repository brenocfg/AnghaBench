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
struct super_block {int /*<<< orphan*/  s_blocksize; } ;
struct ocfs2_block_check {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_SB (struct super_block*) ; 
 int /*<<< orphan*/  ocfs2_block_check_compute (void*,int /*<<< orphan*/ ,struct ocfs2_block_check*) ; 
 scalar_t__ ocfs2_meta_ecc (int /*<<< orphan*/ ) ; 

void ocfs2_compute_meta_ecc(struct super_block *sb, void *data,
			    struct ocfs2_block_check *bc)
{
	if (ocfs2_meta_ecc(OCFS2_SB(sb)))
		ocfs2_block_check_compute(data, sb->s_blocksize, bc);
}