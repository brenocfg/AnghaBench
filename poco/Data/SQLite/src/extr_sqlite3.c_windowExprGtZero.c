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
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_5__ {int /*<<< orphan*/  enc; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_6__ {TYPE_1__* db; } ;
typedef  TYPE_2__ Parse ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_AFF_NUMERIC ; 
 int /*<<< orphan*/  sqlite3ValueFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ValueFromExpr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ sqlite3_value_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int windowExprGtZero(Parse *pParse, Expr *pExpr){
  int ret = 0;
  sqlite3 *db = pParse->db;
  sqlite3_value *pVal = 0;
  sqlite3ValueFromExpr(db, pExpr, db->enc, SQLITE_AFF_NUMERIC, &pVal);
  if( pVal && sqlite3_value_int(pVal)>0 ){
    ret = 1;
  }
  sqlite3ValueFree(pVal);
  return ret;
}