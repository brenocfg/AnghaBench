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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_2__ {scalar_t__ nVar; int expired; scalar_t__ expmask; scalar_t__ isPrepareV2; } ;
typedef  TYPE_1__ Vdbe ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int sqlite3TransferBindings (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int sqlite3_transfer_bindings(sqlite3_stmt *pFromStmt, sqlite3_stmt *pToStmt){
  Vdbe *pFrom = (Vdbe*)pFromStmt;
  Vdbe *pTo = (Vdbe*)pToStmt;
  if( pFrom->nVar!=pTo->nVar ){
    return SQLITE_ERROR;
  }
  if( pTo->isPrepareV2 && pTo->expmask ){
    pTo->expired = 1;
  }
  if( pFrom->isPrepareV2 && pFrom->expmask ){
    pFrom->expired = 1;
  }
  return sqlite3TransferBindings(pFromStmt, pToStmt);
}