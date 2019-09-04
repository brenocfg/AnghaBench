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
struct sym_tcb {int dummy; } ;
struct sym_hcb {int dummy; } ;
struct sym_ccb {scalar_t__ nego_status; int /*<<< orphan*/  target; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS_BUSY ; 
 scalar_t__ HS_NEGOTIATE ; 
 int /*<<< orphan*/  HS_PRT ; 
 scalar_t__ INB (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 scalar_t__ NS_PPR ; 
 int /*<<< orphan*/  OUTB (struct sym_hcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTL_DSP (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCRIPTA_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCRIPTB_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clrack ; 
 int /*<<< orphan*/  msg_bad ; 
 int /*<<< orphan*/  ppr_resp ; 
 int sym_ppr_nego_check (struct sym_hcb*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sym_ppr_nego(struct sym_hcb *np, struct sym_tcb *tp, struct sym_ccb *cp)
{
	int req = 1;
	int result;

	/*
	 *  Request or answer ?
	 */
	if (INB(np, HS_PRT) == HS_NEGOTIATE) {
		OUTB(np, HS_PRT, HS_BUSY);
		if (cp->nego_status && cp->nego_status != NS_PPR)
			goto reject_it;
		req = 0;
	}

	/*
	 *  Check and apply new values.
	 */
	result = sym_ppr_nego_check(np, req, cp->target);
	if (result)	/* Not acceptable, reject it */
		goto reject_it;
	if (req) {	/* Was a request, send response. */
		cp->nego_status = NS_PPR;
		OUTL_DSP(np, SCRIPTB_BA(np, ppr_resp));
	}
	else		/* Was a response, we are done. */
		OUTL_DSP(np, SCRIPTA_BA(np, clrack));
	return;

reject_it:
	OUTL_DSP(np, SCRIPTB_BA(np, msg_bad));
}