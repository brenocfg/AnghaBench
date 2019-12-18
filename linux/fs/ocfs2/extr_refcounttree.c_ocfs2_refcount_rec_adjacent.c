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
struct TYPE_4__ {TYPE_1__* rl_recs; } ;
struct ocfs2_refcount_block {TYPE_2__ rf_records; } ;
typedef  enum ocfs2_ref_rec_contig { ____Placeholder_ocfs2_ref_rec_contig } ocfs2_ref_rec_contig ;
struct TYPE_3__ {scalar_t__ r_refcount; int /*<<< orphan*/  r_cpos; int /*<<< orphan*/  r_clusters; } ;

/* Variables and functions */
 int REF_CONTIG_NONE ; 
 int REF_CONTIG_RIGHT ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ocfs2_ref_rec_contig
	ocfs2_refcount_rec_adjacent(struct ocfs2_refcount_block *rb,
				    int index)
{
	if ((rb->rf_records.rl_recs[index].r_refcount ==
	    rb->rf_records.rl_recs[index + 1].r_refcount) &&
	    (le64_to_cpu(rb->rf_records.rl_recs[index].r_cpos) +
	    le32_to_cpu(rb->rf_records.rl_recs[index].r_clusters) ==
	    le64_to_cpu(rb->rf_records.rl_recs[index + 1].r_cpos)))
		return REF_CONTIG_RIGHT;

	return REF_CONTIG_NONE;
}