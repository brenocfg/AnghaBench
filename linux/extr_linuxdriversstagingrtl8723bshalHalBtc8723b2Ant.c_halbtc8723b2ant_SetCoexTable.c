#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  (* fBtcWrite1Byte ) (TYPE_1__*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* fBtcWrite4Byte ) (TYPE_1__*,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  ALGO_TRACE_SW_EXEC ; 
 int /*<<< orphan*/  BTC_MSG_ALGORITHM ; 
 int /*<<< orphan*/  BTC_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void halbtc8723b2ant_SetCoexTable(
	PBTC_COEXIST pBtCoexist,
	u32 val0x6c0,
	u32 val0x6c4,
	u32 val0x6c8,
	u8 val0x6cc
)
{
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_SW_EXEC,
		("[BTCoex], set coex table, set 0x6c0 = 0x%x\n", val0x6c0)
	);
	pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x6c0, val0x6c0);

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_SW_EXEC,
		("[BTCoex], set coex table, set 0x6c4 = 0x%x\n", val0x6c4)
	);
	pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x6c4, val0x6c4);

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_SW_EXEC,
		("[BTCoex], set coex table, set 0x6c8 = 0x%x\n", val0x6c8)
	);
	pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x6c8, val0x6c8);

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_SW_EXEC,
		("[BTCoex], set coex table, set 0x6cc = 0x%x\n", val0x6cc)
	);
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x6cc, val0x6cc);
}