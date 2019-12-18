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
struct TYPE_4__ {scalar_t__ op; } ;
typedef  int /*<<< orphan*/  NameContext ;
typedef  TYPE_1__ Expr ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ TK_ID ; 
 scalar_t__ TK_STRING ; 
 int sqlite3ResolveExprNames (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int resolveAttachExpr(NameContext *pName, Expr *pExpr)
{
  int rc = SQLITE_OK;
  if( pExpr ){
    if( pExpr->op!=TK_ID ){
      rc = sqlite3ResolveExprNames(pName, pExpr);
    }else{
      pExpr->op = TK_STRING;
    }
  }
  return rc;
}