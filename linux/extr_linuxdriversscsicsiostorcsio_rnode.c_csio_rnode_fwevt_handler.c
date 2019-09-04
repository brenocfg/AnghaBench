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
typedef  size_t uint8_t ;
struct csio_rnode {size_t prev_evt; size_t cur_evt; int /*<<< orphan*/  sm; } ;
struct csio_lnode {int dummy; } ;
typedef  enum csio_rn_ev { ____Placeholder_csio_rn_ev } csio_rn_ev ;

/* Variables and functions */
 int CSIO_FWE_TO_RNFE (size_t) ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_rnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ csio_is_rnode_uninit (struct csio_rnode*) ; 
 int /*<<< orphan*/  csio_ln_err (struct csio_lnode*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  csio_post_event (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  csio_put_rnode (struct csio_lnode*,struct csio_rnode*) ; 
 int /*<<< orphan*/  csio_rn_flowid (struct csio_rnode*) ; 
 struct csio_lnode* csio_rnode_to_lnode (struct csio_rnode*) ; 
 int /*<<< orphan*/ * n_evt_fw ; 
 int /*<<< orphan*/  n_evt_unexp ; 

void
csio_rnode_fwevt_handler(struct csio_rnode *rn, uint8_t fwevt)
{
	struct csio_lnode *ln = csio_rnode_to_lnode(rn);
	enum csio_rn_ev evt;

	evt = CSIO_FWE_TO_RNFE(fwevt);
	if (!evt) {
		csio_ln_err(ln, "ssni:x%x Unhandled FW Rdev event: %d\n",
			    csio_rn_flowid(rn), fwevt);
		CSIO_INC_STATS(rn, n_evt_unexp);
		return;
	}
	CSIO_INC_STATS(rn, n_evt_fw[fwevt]);

	/* Track previous & current events for debugging */
	rn->prev_evt = rn->cur_evt;
	rn->cur_evt = fwevt;

	/* Post event to rnode SM */
	csio_post_event(&rn->sm, evt);

	/* Free rn if in uninit state */
	if (csio_is_rnode_uninit(rn))
		csio_put_rnode(ln, rn);
}