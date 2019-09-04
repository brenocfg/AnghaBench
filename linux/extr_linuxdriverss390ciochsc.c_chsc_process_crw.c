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
struct crw {int /*<<< orphan*/  rsid; int /*<<< orphan*/  erc; int /*<<< orphan*/  anc; int /*<<< orphan*/  rsc; int /*<<< orphan*/  chn; int /*<<< orphan*/  oflw; int /*<<< orphan*/  slct; } ;
struct chsc_sei {int dummy; } ;

/* Variables and functions */
 int CHSC_SEI_NT0 ; 
 int CHSC_SEI_NT2 ; 
 int /*<<< orphan*/  CIO_CRW_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int /*<<< orphan*/  chsc_process_event_information (struct chsc_sei*,int) ; 
 int /*<<< orphan*/  css_schedule_eval_all () ; 
 struct chsc_sei* sei_page ; 

__attribute__((used)) static void chsc_process_crw(struct crw *crw0, struct crw *crw1, int overflow)
{
	struct chsc_sei *sei = sei_page;

	if (overflow) {
		css_schedule_eval_all();
		return;
	}
	CIO_CRW_EVENT(2, "CRW reports slct=%d, oflw=%d, "
		      "chn=%d, rsc=%X, anc=%d, erc=%X, rsid=%X\n",
		      crw0->slct, crw0->oflw, crw0->chn, crw0->rsc, crw0->anc,
		      crw0->erc, crw0->rsid);

	CIO_TRACE_EVENT(2, "prcss");
	chsc_process_event_information(sei, CHSC_SEI_NT0 | CHSC_SEI_NT2);
}