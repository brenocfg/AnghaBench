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
typedef  int /*<<< orphan*/  PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  NORMAL_EXEC ; 
 int /*<<< orphan*/  halbtc8723b2ant_AgcTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  halbtc8723b2ant_DacSwing (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void halbtc8723b2ant_SwMechanism2(
	PBTC_COEXIST pBtCoexist,
	bool bAGCTableShift,
	bool bADCBackOff,
	bool bSWDACSwing,
	u32 dacSwingLvl
)
{
	halbtc8723b2ant_AgcTable(pBtCoexist, NORMAL_EXEC, bAGCTableShift);
	halbtc8723b2ant_DacSwing(pBtCoexist, NORMAL_EXEC, bSWDACSwing, dacSwingLvl);
}