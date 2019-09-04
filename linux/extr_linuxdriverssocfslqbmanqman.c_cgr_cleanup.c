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
typedef  scalar_t__ u32 ;
struct qman_fq {int /*<<< orphan*/  fqid; } ;
struct qm_mcr_queryfq_np {int state; } ;
struct qm_fqd {scalar_t__ cgid; int /*<<< orphan*/  fq_ctrl; } ;

/* Variables and functions */
 int EIO ; 
 int ERANGE ; 
 int QM_FQCTRL_CGE ; 
 int /*<<< orphan*/  QM_FQID_RANGE_START ; 
 int QM_MCR_NP_STATE_MASK ; 
 int QM_MCR_NP_STATE_OOS ; 
 scalar_t__ WARN_ON (int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int qman_query_fq (struct qman_fq*,struct qm_fqd*) ; 
 int qman_query_fq_np (struct qman_fq*,struct qm_mcr_queryfq_np*) ; 

__attribute__((used)) static int cgr_cleanup(u32 cgrid)
{
	/*
	 * query all FQDs starting from FQID 1 until we get an "invalid FQID"
	 * error, looking for non-OOS FQDs whose CGR is the CGR being released
	 */
	struct qman_fq fq = {
		.fqid = QM_FQID_RANGE_START
	};
	int err;

	do {
		struct qm_mcr_queryfq_np np;

		err = qman_query_fq_np(&fq, &np);
		if (err == -ERANGE)
			/* FQID range exceeded, found no problems */
			return 0;
		else if (WARN_ON(err))
			return err;

		if ((np.state & QM_MCR_NP_STATE_MASK) != QM_MCR_NP_STATE_OOS) {
			struct qm_fqd fqd;

			err = qman_query_fq(&fq, &fqd);
			if (WARN_ON(err))
				return err;
			if (be16_to_cpu(fqd.fq_ctrl) & QM_FQCTRL_CGE &&
			    fqd.cgid == cgrid) {
				pr_err("CRGID 0x%x is being used by FQID 0x%x, CGR will be leaked\n",
				       cgrid, fq.fqid);
				return -EIO;
			}
		}
		/* Move to the next FQID */
		fq.fqid++;
	} while (1);
}