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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_extent_list {int /*<<< orphan*/  l_next_free_rec; struct ocfs2_extent_rec* l_recs; void* l_count; } ;
struct ocfs2_group_desc {int /*<<< orphan*/  bg_free_bits_count; int /*<<< orphan*/  bg_bits; struct ocfs2_extent_list bg_list; } ;
struct ocfs2_extent_rec {void* e_leaf_clusters; int /*<<< orphan*/  e_cpos; int /*<<< orphan*/  e_blkno; } ;
struct ocfs2_chain_list {int /*<<< orphan*/  cl_bpc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 void* cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int ocfs2_extent_recs_per_gd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_supports_discontig_bg (struct ocfs2_super*) ; 

__attribute__((used)) static void ocfs2_bg_discontig_add_extent(struct ocfs2_super *osb,
					  struct ocfs2_group_desc *bg,
					  struct ocfs2_chain_list *cl,
					  u64 p_blkno, unsigned int clusters)
{
	struct ocfs2_extent_list *el = &bg->bg_list;
	struct ocfs2_extent_rec *rec;

	BUG_ON(!ocfs2_supports_discontig_bg(osb));
	if (!el->l_next_free_rec)
		el->l_count = cpu_to_le16(ocfs2_extent_recs_per_gd(osb->sb));
	rec = &el->l_recs[le16_to_cpu(el->l_next_free_rec)];
	rec->e_blkno = cpu_to_le64(p_blkno);
	rec->e_cpos = cpu_to_le32(le16_to_cpu(bg->bg_bits) /
				  le16_to_cpu(cl->cl_bpc));
	rec->e_leaf_clusters = cpu_to_le16(clusters);
	le16_add_cpu(&bg->bg_bits, clusters * le16_to_cpu(cl->cl_bpc));
	le16_add_cpu(&bg->bg_free_bits_count,
		     clusters * le16_to_cpu(cl->cl_bpc));
	le16_add_cpu(&el->l_next_free_rec, 1);
}