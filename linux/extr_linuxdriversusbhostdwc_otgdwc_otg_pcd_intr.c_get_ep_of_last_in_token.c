#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_13__ {int dtknqr1; int volatile dvbusdis; int dtknqr3_dthrctl; } ;
typedef  TYPE_5__ dwc_otg_device_global_regs_t ;
struct TYPE_10__ {int dev_token_q_depth; } ;
struct TYPE_11__ {TYPE_2__ b; } ;
struct TYPE_14__ {TYPE_3__ hwcfg2; TYPE_1__* dev_if; } ;
typedef  TYPE_6__ dwc_otg_core_if_t ;
struct TYPE_12__ {int epnums0_5; int intknwptr; } ;
struct TYPE_15__ {int d32; TYPE_4__ b; } ;
typedef  TYPE_7__ dtknq1_data_t ;
struct TYPE_9__ {TYPE_5__* dev_global_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCDV ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int,int) ; 
 int DWC_READ_REG32 (int volatile*) ; 

__attribute__((used)) static inline int get_ep_of_last_in_token(dwc_otg_core_if_t * core_if)
{
	dwc_otg_device_global_regs_t *dev_global_regs =
	    core_if->dev_if->dev_global_regs;
	const uint32_t TOKEN_Q_DEPTH = core_if->hwcfg2.b.dev_token_q_depth;
	/* Number of Token Queue Registers */
	const int DTKNQ_REG_CNT = (TOKEN_Q_DEPTH + 7) / 8;
	dtknq1_data_t dtknqr1;
	uint32_t in_tkn_epnums[4];
	int ndx = 0;
	int i = 0;
	volatile uint32_t *addr = &dev_global_regs->dtknqr1;
	int epnum = 0;

	//DWC_DEBUGPL(DBG_PCD,"dev_token_q_depth=%d\n",TOKEN_Q_DEPTH);

	/* Read the DTKNQ Registers */
	for (i = 0; i < DTKNQ_REG_CNT; i++) {
		in_tkn_epnums[i] = DWC_READ_REG32(addr);
		DWC_DEBUGPL(DBG_PCDV, "DTKNQR%d=0x%08x\n", i + 1,
			    in_tkn_epnums[i]);
		if (addr == &dev_global_regs->dvbusdis) {
			addr = &dev_global_regs->dtknqr3_dthrctl;
		} else {
			++addr;
		}

	}

	/* Copy the DTKNQR1 data to the bit field. */
	dtknqr1.d32 = in_tkn_epnums[0];
	/* Get the EP numbers */
	in_tkn_epnums[0] = dtknqr1.b.epnums0_5;
	ndx = dtknqr1.b.intknwptr - 1;

	//DWC_DEBUGPL(DBG_PCDV,"ndx=%d\n",ndx);
	if (ndx == -1) {
		/** @todo Find a simpler way to calculate the max
		 * queue position.*/
		int cnt = TOKEN_Q_DEPTH;
		if (TOKEN_Q_DEPTH <= 6) {
			cnt = TOKEN_Q_DEPTH - 1;
		} else if (TOKEN_Q_DEPTH <= 14) {
			cnt = TOKEN_Q_DEPTH - 7;
		} else if (TOKEN_Q_DEPTH <= 22) {
			cnt = TOKEN_Q_DEPTH - 15;
		} else {
			cnt = TOKEN_Q_DEPTH - 23;
		}
		epnum = (in_tkn_epnums[DTKNQ_REG_CNT - 1] >> (cnt * 4)) & 0xF;
	} else {
		if (ndx <= 5) {
			epnum = (in_tkn_epnums[0] >> (ndx * 4)) & 0xF;
		} else if (ndx <= 13) {
			ndx -= 6;
			epnum = (in_tkn_epnums[1] >> (ndx * 4)) & 0xF;
		} else if (ndx <= 21) {
			ndx -= 14;
			epnum = (in_tkn_epnums[2] >> (ndx * 4)) & 0xF;
		} else if (ndx <= 29) {
			ndx -= 22;
			epnum = (in_tkn_epnums[3] >> (ndx * 4)) & 0xF;
		}
	}
	//DWC_DEBUGPL(DBG_PCD,"epnum=%d\n",epnum);
	return epnum;
}