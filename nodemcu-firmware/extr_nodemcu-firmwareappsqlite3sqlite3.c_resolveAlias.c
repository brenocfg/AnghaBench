#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_22__ {int /*<<< orphan*/  zToken; } ;
struct TYPE_25__ {scalar_t__ op; int flags; TYPE_2__ u; } ;
struct TYPE_24__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_23__ {int /*<<< orphan*/ * db; } ;
struct TYPE_21__ {TYPE_5__* pExpr; } ;
typedef  TYPE_3__ Parse ;
typedef  TYPE_4__ ExprList ;
typedef  TYPE_5__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_Alias ; 
 int /*<<< orphan*/  EP_IntValue ; 
 int EP_MemToken ; 
 int EP_Reduced ; 
 int /*<<< orphan*/  EP_Static ; 
 int EP_TokenOnly ; 
 int /*<<< orphan*/  ExprHasProperty (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExprSetProperty (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TK_COLLATE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  incrAggFunctionDepth (TYPE_5__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3DbStrDup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* sqlite3ExprAddCollateString (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ *,TYPE_5__*) ; 
 TYPE_5__* sqlite3ExprDup (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resolveAlias(
  Parse *pParse,         /* Parsing context */
  ExprList *pEList,      /* A result set */
  int iCol,              /* A column in the result set.  0..pEList->nExpr-1 */
  Expr *pExpr,           /* Transform this into an alias to the result set */
  const char *zType,     /* "GROUP" or "ORDER" or "" */
  int nSubquery          /* Number of subqueries that the label is moving */
){
  Expr *pOrig;           /* The iCol-th column of the result set */
  Expr *pDup;            /* Copy of pOrig */
  sqlite3 *db;           /* The database connection */

  assert( iCol>=0 && iCol<pEList->nExpr );
  pOrig = pEList->a[iCol].pExpr;
  assert( pOrig!=0 );
  db = pParse->db;
  pDup = sqlite3ExprDup(db, pOrig, 0);
  if( pDup==0 ) return;
  if( zType[0]!='G' ) incrAggFunctionDepth(pDup, nSubquery);
  if( pExpr->op==TK_COLLATE ){
    pDup = sqlite3ExprAddCollateString(pParse, pDup, pExpr->u.zToken);
  }
  ExprSetProperty(pDup, EP_Alias);

  /* Before calling sqlite3ExprDelete(), set the EP_Static flag. This
  ** prevents ExprDelete() from deleting the Expr structure itself,
  ** allowing it to be repopulated by the memcpy() on the following line.
  ** The pExpr->u.zToken might point into memory that will be freed by the
  ** sqlite3DbFree(db, pDup) on the last line of this block, so be sure to
  ** make a copy of the token before doing the sqlite3DbFree().
  */
  ExprSetProperty(pExpr, EP_Static);
  sqlite3ExprDelete(db, pExpr);
  memcpy(pExpr, pDup, sizeof(*pExpr));
  if( !ExprHasProperty(pExpr, EP_IntValue) && pExpr->u.zToken!=0 ){
    assert( (pExpr->flags & (EP_Reduced|EP_TokenOnly))==0 );
    pExpr->u.zToken = sqlite3DbStrDup(db, pExpr->u.zToken);
    pExpr->flags |= EP_MemToken;
  }
  sqlite3DbFree(db, pDup);
}