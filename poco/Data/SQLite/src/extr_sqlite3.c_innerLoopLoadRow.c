#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  db; } ;
struct TYPE_9__ {scalar_t__ pExtra; int /*<<< orphan*/  regExtraResult; int /*<<< orphan*/  ecelFlags; int /*<<< orphan*/  regResult; } ;
struct TYPE_8__ {scalar_t__ pEList; } ;
typedef  TYPE_1__ Select ;
typedef  TYPE_2__ RowLoadInfo ;
typedef  TYPE_3__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3ExprCodeExprList (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void innerLoopLoadRow(
  Parse *pParse,             /* Statement under construction */
  Select *pSelect,           /* The query being coded */
  RowLoadInfo *pInfo         /* Info needed to complete the row load */
){
  sqlite3ExprCodeExprList(pParse, pSelect->pEList, pInfo->regResult,
                          0, pInfo->ecelFlags);
#ifdef SQLITE_ENABLE_SORTER_REFERENCES
  if( pInfo->pExtra ){
    sqlite3ExprCodeExprList(pParse, pInfo->pExtra, pInfo->regExtraResult, 0, 0);
    sqlite3ExprListDelete(pParse->db, pInfo->pExtra);
  }
#endif
}