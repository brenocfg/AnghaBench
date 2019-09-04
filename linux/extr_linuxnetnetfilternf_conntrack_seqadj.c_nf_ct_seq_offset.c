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
typedef  int /*<<< orphan*/  u32 ;
struct nf_ct_seqadj {int /*<<< orphan*/  offset_before; int /*<<< orphan*/  offset_after; int /*<<< orphan*/  correction_pos; } ;
struct nf_conn_seqadj {struct nf_ct_seqadj* seq; } ;
struct nf_conn {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;

/* Variables and functions */
 scalar_t__ after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nf_conn_seqadj* nfct_seqadj (struct nf_conn const*) ; 

s32 nf_ct_seq_offset(const struct nf_conn *ct,
		     enum ip_conntrack_dir dir,
		     u32 seq)
{
	struct nf_conn_seqadj *seqadj = nfct_seqadj(ct);
	struct nf_ct_seqadj *this_way;

	if (!seqadj)
		return 0;

	this_way = &seqadj->seq[dir];
	return after(seq, this_way->correction_pos) ?
		 this_way->offset_after : this_way->offset_before;
}