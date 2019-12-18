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
struct nlattr {int dummy; } ;
struct nf_ct_seqadj {void* offset_after; void* offset_before; void* correction_pos; } ;

/* Variables and functions */
 size_t CTA_SEQADJ_CORRECTION_POS ; 
 int /*<<< orphan*/  CTA_SEQADJ_MAX ; 
 size_t CTA_SEQADJ_OFFSET_AFTER ; 
 size_t CTA_SEQADJ_OFFSET_BEFORE ; 
 int EINVAL ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seqadj_policy ; 

__attribute__((used)) static int change_seq_adj(struct nf_ct_seqadj *seq,
			  const struct nlattr * const attr)
{
	int err;
	struct nlattr *cda[CTA_SEQADJ_MAX+1];

	err = nla_parse_nested_deprecated(cda, CTA_SEQADJ_MAX, attr,
					  seqadj_policy, NULL);
	if (err < 0)
		return err;

	if (!cda[CTA_SEQADJ_CORRECTION_POS])
		return -EINVAL;

	seq->correction_pos =
		ntohl(nla_get_be32(cda[CTA_SEQADJ_CORRECTION_POS]));

	if (!cda[CTA_SEQADJ_OFFSET_BEFORE])
		return -EINVAL;

	seq->offset_before =
		ntohl(nla_get_be32(cda[CTA_SEQADJ_OFFSET_BEFORE]));

	if (!cda[CTA_SEQADJ_OFFSET_AFTER])
		return -EINVAL;

	seq->offset_after =
		ntohl(nla_get_be32(cda[CTA_SEQADJ_OFFSET_AFTER]));

	return 0;
}