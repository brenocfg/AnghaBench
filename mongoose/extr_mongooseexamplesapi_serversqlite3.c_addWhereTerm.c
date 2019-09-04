#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  scalar_t__ i16 ;
struct TYPE_23__ {scalar_t__ iTable; scalar_t__ iRightJoinTable; } ;
struct TYPE_22__ {int /*<<< orphan*/ * db; } ;
struct TYPE_21__ {int nSrc; TYPE_1__* a; } ;
struct TYPE_20__ {int pTab; } ;
typedef  TYPE_2__ SrcList ;
typedef  TYPE_3__ Parse ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FromJoin ; 
 int EP_Reduced ; 
 int EP_TokenOnly ; 
 int /*<<< orphan*/  ExprHasAnyProperty (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ExprSetIrreducible (TYPE_4__*) ; 
 int /*<<< orphan*/  ExprSetProperty (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TK_EQ ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__* sqlite3CreateColumnExpr (int /*<<< orphan*/ *,TYPE_2__*,int,int) ; 
 TYPE_4__* sqlite3ExprAnd (int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* sqlite3PExpr (TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void addWhereTerm(
  Parse *pParse,                  /* Parsing context */
  SrcList *pSrc,                  /* List of tables in FROM clause */
  int iLeft,                      /* Index of first table to join in pSrc */
  int iColLeft,                   /* Index of column in first table */
  int iRight,                     /* Index of second table in pSrc */
  int iColRight,                  /* Index of column in second table */
  int isOuterJoin,                /* True if this is an OUTER join */
  Expr **ppWhere                  /* IN/OUT: The WHERE clause to add to */
){
  sqlite3 *db = pParse->db;
  Expr *pE1;
  Expr *pE2;
  Expr *pEq;

  assert( iLeft<iRight );
  assert( pSrc->nSrc>iRight );
  assert( pSrc->a[iLeft].pTab );
  assert( pSrc->a[iRight].pTab );

  pE1 = sqlite3CreateColumnExpr(db, pSrc, iLeft, iColLeft);
  pE2 = sqlite3CreateColumnExpr(db, pSrc, iRight, iColRight);

  pEq = sqlite3PExpr(pParse, TK_EQ, pE1, pE2, 0);
  if( pEq && isOuterJoin ){
    ExprSetProperty(pEq, EP_FromJoin);
    assert( !ExprHasAnyProperty(pEq, EP_TokenOnly|EP_Reduced) );
    ExprSetIrreducible(pEq);
    pEq->iRightJoinTable = (i16)pE2->iTable;
  }
  *ppWhere = sqlite3ExprAnd(db, *ppWhere, pEq);
}