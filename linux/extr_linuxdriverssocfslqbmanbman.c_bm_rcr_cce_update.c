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
struct bm_rcr {int ci; scalar_t__ cmode; int /*<<< orphan*/  available; } ;
struct bm_portal {struct bm_rcr rcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_CL_RCR_CI_CENA ; 
 int BM_RCR_SIZE ; 
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int bm_ce_in (struct bm_portal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_cl_invalidate (struct bm_portal*,int /*<<< orphan*/ ) ; 
 scalar_t__ bm_rcr_cce ; 
 int dpaa_cyc_diff (int,int,int) ; 

__attribute__((used)) static u8 bm_rcr_cce_update(struct bm_portal *portal)
{
	struct bm_rcr *rcr = &portal->rcr;
	u8 diff, old_ci = rcr->ci;

	DPAA_ASSERT(rcr->cmode == bm_rcr_cce);
	rcr->ci = bm_ce_in(portal, BM_CL_RCR_CI_CENA) & (BM_RCR_SIZE - 1);
	bm_cl_invalidate(portal, BM_CL_RCR_CI_CENA);
	diff = dpaa_cyc_diff(BM_RCR_SIZE, old_ci, rcr->ci);
	rcr->available += diff;
	return diff;
}