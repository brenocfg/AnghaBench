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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_2__ {scalar_t__* aCounter; } ;
typedef  TYPE_1__ Vdbe ;

/* Variables and functions */

int sqlite3_stmt_status(sqlite3_stmt *pStmt, int op, int resetFlag){
  Vdbe *pVdbe = (Vdbe*)pStmt;
  u32 v;
#ifdef SQLITE_ENABLE_API_ARMOR
  if( !pStmt ){
    (void)SQLITE_MISUSE_BKPT;
    return 0;
  }
#endif
  v = pVdbe->aCounter[op];
  if( resetFlag ) pVdbe->aCounter[op] = 0;
  return (int)v;
}