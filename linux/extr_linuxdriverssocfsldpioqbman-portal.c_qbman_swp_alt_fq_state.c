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
typedef  int u8 ;
typedef  int u32 ;
struct qbman_swp {int dummy; } ;
struct qbman_alt_fq_state_rslt {int verb; scalar_t__ rslt; } ;
struct qbman_alt_fq_state_desc {int /*<<< orphan*/  fqid; } ;

/* Variables and functions */
 int ALT_FQ_FQID_MASK ; 
 int EBUSY ; 
 int EIO ; 
 scalar_t__ QBMAN_MC_RSLT_OK ; 
 int QBMAN_RESULT_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 struct qbman_alt_fq_state_rslt* qbman_swp_mc_complete (struct qbman_swp*,struct qbman_alt_fq_state_desc*,int) ; 
 struct qbman_alt_fq_state_desc* qbman_swp_mc_start (struct qbman_swp*) ; 
 scalar_t__ unlikely (int) ; 

int qbman_swp_alt_fq_state(struct qbman_swp *s, u32 fqid,
			   u8 alt_fq_verb)
{
	struct qbman_alt_fq_state_desc *p;
	struct qbman_alt_fq_state_rslt *r;

	/* Start the management command */
	p = qbman_swp_mc_start(s);
	if (!p)
		return -EBUSY;

	p->fqid = cpu_to_le32(fqid & ALT_FQ_FQID_MASK);

	/* Complete the management command */
	r = qbman_swp_mc_complete(s, p, alt_fq_verb);
	if (unlikely(!r)) {
		pr_err("qbman: mgmt cmd failed, no response (verb=0x%x)\n",
		       alt_fq_verb);
		return -EIO;
	}

	/* Decode the outcome */
	WARN_ON((r->verb & QBMAN_RESULT_MASK) != alt_fq_verb);

	/* Determine success or failure */
	if (unlikely(r->rslt != QBMAN_MC_RSLT_OK)) {
		pr_err("qbman: ALT FQID %d failed: verb = 0x%08x code = 0x%02x\n",
		       fqid, r->verb, r->rslt);
		return -EIO;
	}

	return 0;
}