#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  (* fBtcFillH2c ) (TYPE_1__*,int,int,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE_FW_EXEC ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void halbtc8723b2ant_SetFwDecBtPwr(
	PBTC_COEXIST pBtCoexist, u8 decBtPwrLvl
)
{
	u8 	H2C_Parameter[1] = {0};

	H2C_Parameter[0] = decBtPwrLvl;

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW_EXEC,
		(
			"[BTCoex], decrease Bt Power level = %d, FW write 0x62 = 0x%x\n",
			decBtPwrLvl,
			H2C_Parameter[0]
		)
	);

	pBtCoexist->fBtcFillH2c(pBtCoexist, 0x62, 1, H2C_Parameter);
}