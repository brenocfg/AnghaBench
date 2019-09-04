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
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_QSTS (int) ; 
 int AR_Q_STS_PEND_FR_CNT ; 
 int /*<<< orphan*/  AR_Q_TXE ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 

u32 ath9k_hw_numtxpending(struct ath_hw *ah, u32 q)
{
	u32 npend;

	npend = REG_READ(ah, AR_QSTS(q)) & AR_Q_STS_PEND_FR_CNT;
	if (npend == 0) {

		if (REG_READ(ah, AR_Q_TXE) & (1 << q))
			npend = 1;
	}

	return npend;
}