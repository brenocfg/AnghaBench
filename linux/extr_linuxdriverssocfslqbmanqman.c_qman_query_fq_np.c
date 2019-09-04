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
struct qm_mcr_queryfq_np {int dummy; } ;
union qm_mc_result {int verb; scalar_t__ result; struct qm_mcr_queryfq_np queryfq_np; } ;
union qm_mc_command {int /*<<< orphan*/  fq; } ;
struct qman_portal {int /*<<< orphan*/  p; } ;
struct qman_fq {int /*<<< orphan*/  fqid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int EIO ; 
 int ERANGE ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  QM_MCC_VERB_QUERYFQ_NP ; 
 scalar_t__ QM_MCR_RESULT_ERR_FQID ; 
 scalar_t__ QM_MCR_RESULT_OK ; 
 int QM_MCR_VERB_MASK ; 
 int QM_MCR_VERB_QUERYFQ_NP ; 
 struct qman_portal* get_affine_portal () ; 
 int /*<<< orphan*/  put_affine_portal () ; 
 int /*<<< orphan*/  qm_fqid_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_mc_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_mc_result_timeout (int /*<<< orphan*/ *,union qm_mc_result**) ; 
 union qm_mc_command* qm_mc_start (int /*<<< orphan*/ *) ; 

int qman_query_fq_np(struct qman_fq *fq, struct qm_mcr_queryfq_np *np)
{
	union qm_mc_command *mcc;
	union qm_mc_result *mcr;
	struct qman_portal *p = get_affine_portal();
	int ret = 0;

	mcc = qm_mc_start(&p->p);
	qm_fqid_set(&mcc->fq, fq->fqid);
	qm_mc_commit(&p->p, QM_MCC_VERB_QUERYFQ_NP);
	if (!qm_mc_result_timeout(&p->p, &mcr)) {
		ret = -ETIMEDOUT;
		goto out;
	}

	DPAA_ASSERT((mcr->verb & QM_MCR_VERB_MASK) == QM_MCR_VERB_QUERYFQ_NP);
	if (mcr->result == QM_MCR_RESULT_OK)
		*np = mcr->queryfq_np;
	else if (mcr->result == QM_MCR_RESULT_ERR_FQID)
		ret = -ERANGE;
	else
		ret = -EIO;
out:
	put_affine_portal();
	return ret;
}