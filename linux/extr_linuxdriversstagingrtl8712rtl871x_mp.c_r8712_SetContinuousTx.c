#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ curr_rateidx; } ;
struct _adapter {TYPE_1__ mppriv; } ;

/* Variables and functions */
 scalar_t__ MPT_RATE_11M ; 
 scalar_t__ MPT_RATE_6M ; 
 scalar_t__ MPT_RATE_MCS15 ; 
 int /*<<< orphan*/  SetCCKContinuousTx (struct _adapter*,scalar_t__) ; 
 int /*<<< orphan*/  SetOFDMContinuousTx (struct _adapter*,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int r8712_bb_reg_read (struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_bb_reg_write (struct _adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rRx_Wait_CCCA ; 

void r8712_SetContinuousTx(struct _adapter *pAdapter, u8 bStart)
{
	/* ADC turn off [bit24-21] adc port0 ~ port1 */
	if (bStart) {
		r8712_bb_reg_write(pAdapter, rRx_Wait_CCCA,
				   r8712_bb_reg_read(pAdapter,
				   rRx_Wait_CCCA) & 0xFE1FFFFF);
		msleep(100);
	}
	if (pAdapter->mppriv.curr_rateidx <= MPT_RATE_11M)
		SetCCKContinuousTx(pAdapter, bStart);
	else if ((pAdapter->mppriv.curr_rateidx >= MPT_RATE_6M) &&
		 (pAdapter->mppriv.curr_rateidx <= MPT_RATE_MCS15))
		SetOFDMContinuousTx(pAdapter, bStart);
	/* ADC turn on [bit24-21] adc port0 ~ port1 */
	if (!bStart)
		r8712_bb_reg_write(pAdapter, rRx_Wait_CCCA,
				   r8712_bb_reg_read(pAdapter,
				   rRx_Wait_CCCA) | 0x01E00000);
}