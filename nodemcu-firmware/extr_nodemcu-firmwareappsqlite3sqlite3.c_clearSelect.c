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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {scalar_t__ pWith; int /*<<< orphan*/  pOffset; int /*<<< orphan*/  pLimit; int /*<<< orphan*/  pOrderBy; int /*<<< orphan*/  pHaving; int /*<<< orphan*/  pGroupBy; int /*<<< orphan*/  pWhere; int /*<<< orphan*/  pSrc; int /*<<< orphan*/  pEList; struct TYPE_4__* pPrior; } ;
typedef  TYPE_1__ Select ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3DbFreeNN (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SrcListDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3WithDelete (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void clearSelect(sqlite3 *db, Select *p, int bFree){
  while( p ){
    Select *pPrior = p->pPrior;
    sqlite3ExprListDelete(db, p->pEList);
    sqlite3SrcListDelete(db, p->pSrc);
    sqlite3ExprDelete(db, p->pWhere);
    sqlite3ExprListDelete(db, p->pGroupBy);
    sqlite3ExprDelete(db, p->pHaving);
    sqlite3ExprListDelete(db, p->pOrderBy);
    sqlite3ExprDelete(db, p->pLimit);
    sqlite3ExprDelete(db, p->pOffset);
    if( p->pWith ) sqlite3WithDelete(db, p->pWith);
    if( bFree ) sqlite3DbFreeNN(db, p);
    p = pPrior;
    bFree = 1;
  }
}