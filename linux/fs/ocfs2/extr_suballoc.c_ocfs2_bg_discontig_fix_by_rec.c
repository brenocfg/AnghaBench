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
struct ocfs2_suballoc_result {unsigned int sr_bit_offset; unsigned int sr_blkno; unsigned int sr_bits; } ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_blkno; int /*<<< orphan*/  e_leaf_clusters; int /*<<< orphan*/  e_cpos; } ;
struct ocfs2_chain_list {int /*<<< orphan*/  cl_bpc; } ;

/* Variables and functions */
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_bg_discontig_fix_by_rec(struct ocfs2_suballoc_result *res,
					 struct ocfs2_extent_rec *rec,
					 struct ocfs2_chain_list *cl)
{
	unsigned int bpc = le16_to_cpu(cl->cl_bpc);
	unsigned int bitoff = le32_to_cpu(rec->e_cpos) * bpc;
	unsigned int bitcount = le16_to_cpu(rec->e_leaf_clusters) * bpc;

	if (res->sr_bit_offset < bitoff)
		return 0;
	if (res->sr_bit_offset >= (bitoff + bitcount))
		return 0;
	res->sr_blkno = le64_to_cpu(rec->e_blkno) +
		(res->sr_bit_offset - bitoff);
	if ((res->sr_bit_offset + res->sr_bits) > (bitoff + bitcount))
		res->sr_bits = (bitoff + bitcount) - res->sr_bit_offset;
	return 1;
}