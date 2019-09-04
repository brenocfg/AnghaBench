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
struct ptp_dte {int ts_ovf_last; int ts_wrap_cnt; int /*<<< orphan*/  regs; } ;
typedef  int s64 ;

/* Variables and functions */
 int BIT_ULL (int /*<<< orphan*/ ) ; 
 int DTE_NCO_TS_WRAP_LSHIFT ; 
 int DTE_NCO_TS_WRAP_MASK ; 
 int /*<<< orphan*/  DTE_WRAP_AROUND_NSEC_SHIFT ; 
 int dte_read_nco (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s64 dte_read_nco_with_ovf(struct ptp_dte *ptp_dte)
{
	u32 ts_ovf;
	s64 ns = 0;

	ns = dte_read_nco(ptp_dte->regs);

	/*Timestamp overflow: 8 LSB bits of sum3, 4 MSB bits of sum2 */
	ts_ovf = (ns >> DTE_NCO_TS_WRAP_LSHIFT) & DTE_NCO_TS_WRAP_MASK;

	/* Check for wrap around */
	if (ts_ovf < ptp_dte->ts_ovf_last)
		ptp_dte->ts_wrap_cnt++;

	ptp_dte->ts_ovf_last = ts_ovf;

	/* adjust for wraparounds */
	ns += (s64)(BIT_ULL(DTE_WRAP_AROUND_NSEC_SHIFT) * ptp_dte->ts_wrap_cnt);

	return ns;
}