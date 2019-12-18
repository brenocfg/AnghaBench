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
typedef  int u32 ;
struct tcf_mpls_params {int tcfm_label; int tcfm_ttl; int tcfm_tc; int tcfm_bos; } ;
struct mpls_shim_hdr {int /*<<< orphan*/  label_stack_entry; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ACT_MPLS_BOS_NOT_SET ; 
 int ACT_MPLS_LABEL_NOT_SET ; 
 int ACT_MPLS_TC_NOT_SET ; 
 int MPLS_LS_LABEL_MASK ; 
 int MPLS_LS_LABEL_SHIFT ; 
 int MPLS_LS_S_MASK ; 
 int MPLS_LS_S_SHIFT ; 
 int MPLS_LS_TC_MASK ; 
 int MPLS_LS_TC_SHIFT ; 
 int MPLS_LS_TTL_MASK ; 
 int MPLS_LS_TTL_SHIFT ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 

__attribute__((used)) static __be32 tcf_mpls_get_lse(struct mpls_shim_hdr *lse,
			       struct tcf_mpls_params *p, bool set_bos)
{
	u32 new_lse = 0;

	if (lse)
		new_lse = be32_to_cpu(lse->label_stack_entry);

	if (p->tcfm_label != ACT_MPLS_LABEL_NOT_SET) {
		new_lse &= ~MPLS_LS_LABEL_MASK;
		new_lse |= p->tcfm_label << MPLS_LS_LABEL_SHIFT;
	}
	if (p->tcfm_ttl) {
		new_lse &= ~MPLS_LS_TTL_MASK;
		new_lse |= p->tcfm_ttl << MPLS_LS_TTL_SHIFT;
	}
	if (p->tcfm_tc != ACT_MPLS_TC_NOT_SET) {
		new_lse &= ~MPLS_LS_TC_MASK;
		new_lse |= p->tcfm_tc << MPLS_LS_TC_SHIFT;
	}
	if (p->tcfm_bos != ACT_MPLS_BOS_NOT_SET) {
		new_lse &= ~MPLS_LS_S_MASK;
		new_lse |= p->tcfm_bos << MPLS_LS_S_SHIFT;
	} else if (set_bos) {
		new_lse |= 1 << MPLS_LS_S_SHIFT;
	}

	return cpu_to_be32(new_lse);
}