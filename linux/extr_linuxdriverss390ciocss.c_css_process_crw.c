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
struct subchannel_id {int sch_no; int ssid; } ;
struct subchannel {int /*<<< orphan*/  dev; } ;
struct crw {scalar_t__ erc; int rsid; int /*<<< orphan*/  anc; int /*<<< orphan*/  rsc; int /*<<< orphan*/  chn; int /*<<< orphan*/  oflw; int /*<<< orphan*/  slct; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_CRW_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ CRW_ERC_PMOD ; 
 int /*<<< orphan*/  css_evaluate_subchannel (struct subchannel_id,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  css_schedule_eval_all () ; 
 int /*<<< orphan*/  css_update_ssd_info (struct subchannel*) ; 
 struct subchannel* get_subchannel_by_schid (struct subchannel_id) ; 
 int /*<<< orphan*/  init_subchannel_id (struct subchannel_id*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void css_process_crw(struct crw *crw0, struct crw *crw1, int overflow)
{
	struct subchannel_id mchk_schid;
	struct subchannel *sch;

	if (overflow) {
		css_schedule_eval_all();
		return;
	}
	CIO_CRW_EVENT(2, "CRW0 reports slct=%d, oflw=%d, "
		      "chn=%d, rsc=%X, anc=%d, erc=%X, rsid=%X\n",
		      crw0->slct, crw0->oflw, crw0->chn, crw0->rsc, crw0->anc,
		      crw0->erc, crw0->rsid);
	if (crw1)
		CIO_CRW_EVENT(2, "CRW1 reports slct=%d, oflw=%d, "
			      "chn=%d, rsc=%X, anc=%d, erc=%X, rsid=%X\n",
			      crw1->slct, crw1->oflw, crw1->chn, crw1->rsc,
			      crw1->anc, crw1->erc, crw1->rsid);
	init_subchannel_id(&mchk_schid);
	mchk_schid.sch_no = crw0->rsid;
	if (crw1)
		mchk_schid.ssid = (crw1->rsid >> 4) & 3;

	if (crw0->erc == CRW_ERC_PMOD) {
		sch = get_subchannel_by_schid(mchk_schid);
		if (sch) {
			css_update_ssd_info(sch);
			put_device(&sch->dev);
		}
	}
	/*
	 * Since we are always presented with IPI in the CRW, we have to
	 * use stsch() to find out if the subchannel in question has come
	 * or gone.
	 */
	css_evaluate_subchannel(mchk_schid, 0);
}