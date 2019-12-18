#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  i16 ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_5__ {int /*<<< orphan*/ * pTab; } ;
struct TYPE_6__ {int iTable; int /*<<< orphan*/  iColumn; TYPE_1__ y; } ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  TK_COLUMN ; 
 TYPE_2__* sqlite3Expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Expr *exprTableColumn(
  sqlite3 *db,      /* The database connection */
  Table *pTab,      /* The table whose column is desired */
  int iCursor,      /* The open cursor on the table */
  i16 iCol          /* The column that is wanted */
){
  Expr *pExpr = sqlite3Expr(db, TK_COLUMN, 0);
  if( pExpr ){
    pExpr->y.pTab = pTab;
    pExpr->iTable = iCursor;
    pExpr->iColumn = iCol;
  }
  return pExpr;
}