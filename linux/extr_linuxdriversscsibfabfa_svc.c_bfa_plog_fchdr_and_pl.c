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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fchs_s {int dummy; } ;
struct bfa_plog_s {scalar_t__ plog_enabled; } ;
struct bfa_plog_rec_s {int dummy; } ;
typedef  enum bfa_plog_mid { ____Placeholder_bfa_plog_mid } bfa_plog_mid ;
typedef  enum bfa_plog_eid { ____Placeholder_bfa_plog_eid } bfa_plog_eid ;

/* Variables and functions */
 int BFA_PL_INT_LOG_SZ ; 
 int /*<<< orphan*/  bfa_plog_intarr (struct bfa_plog_s*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct bfa_plog_rec_s*,int /*<<< orphan*/ ,int) ; 

void
bfa_plog_fchdr_and_pl(struct bfa_plog_s *plog, enum bfa_plog_mid mid,
		      enum bfa_plog_eid event, u16 misc, struct fchs_s *fchdr,
		      u32 pld_w0)
{
	struct bfa_plog_rec_s  lp;
	u32	*tmp_int = (u32 *) fchdr;
	u32	ints[BFA_PL_INT_LOG_SZ];

	if (plog->plog_enabled) {
		memset(&lp, 0, sizeof(struct bfa_plog_rec_s));

		ints[0] = tmp_int[0];
		ints[1] = tmp_int[1];
		ints[2] = tmp_int[4];
		ints[3] = pld_w0;

		bfa_plog_intarr(plog, mid, event, misc, ints, 4);
	}
}