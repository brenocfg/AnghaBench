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
typedef  int /*<<< orphan*/  PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_BT_MONITOR ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  halbtc8723b1ant_LowPenaltyRa (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void halbtc8723b1ant_SwMechanism(
	PBTC_COEXIST pBtCoexist, bool bLowPenaltyRA
)
{
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_BT_MONITOR,
		("[BTCoex], SM[LpRA] = %d\n", bLowPenaltyRA)
	);

	halbtc8723b1ant_LowPenaltyRa(pBtCoexist, NORMAL_EXEC, bLowPenaltyRA);
}