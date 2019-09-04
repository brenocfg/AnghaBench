#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_7__ {scalar_t__ op; int /*<<< orphan*/  pRight; } ;
struct TYPE_6__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ Parse ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  IN_RENAME_OBJECT ; 
 scalar_t__ TK_NULL ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void binaryToUnaryIfNull(Parse *pParse, Expr *pY, Expr *pA, int op){
    sqlite3 *db = pParse->db;
    if( pA && pY && pY->op==TK_NULL && !IN_RENAME_OBJECT ){
      pA->op = (u8)op;
      sqlite3ExprDelete(db, pA->pRight);
      pA->pRight = 0;
    }
  }