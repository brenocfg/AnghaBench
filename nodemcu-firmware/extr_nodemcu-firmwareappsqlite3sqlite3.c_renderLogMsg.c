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
typedef  int /*<<< orphan*/  zMsg ;
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_2__ {int /*<<< orphan*/  pLogArg; int /*<<< orphan*/  (* xLog ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  StrAccum ;

/* Variables and functions */
 int SQLITE_PRINT_BUF_SIZE ; 
 TYPE_1__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  sqlite3StrAccumFinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3StrAccumInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VXPrintf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void renderLogMsg(int iErrCode, const char *zFormat, va_list ap){
  StrAccum acc;                          /* String accumulator */
  char zMsg[SQLITE_PRINT_BUF_SIZE*3];    /* Complete log message */

  sqlite3StrAccumInit(&acc, 0, zMsg, sizeof(zMsg), 0);
  sqlite3VXPrintf(&acc, zFormat, ap);
  sqlite3GlobalConfig.xLog(sqlite3GlobalConfig.pLogArg, iErrCode,
                           sqlite3StrAccumFinish(&acc));
}