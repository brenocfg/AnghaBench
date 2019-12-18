#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_14__ {int suppressErr; } ;
typedef  TYPE_3__ sqlite3 ;
typedef  int /*<<< orphan*/  nc ;
struct TYPE_18__ {int nExpr; TYPE_2__* a; } ;
struct TYPE_12__ {TYPE_7__* pEList; } ;
struct TYPE_17__ {int ncFlags; scalar_t__ nErr; TYPE_1__ uNC; int /*<<< orphan*/  pSrcList; TYPE_5__* pParse; } ;
struct TYPE_16__ {TYPE_3__* db; } ;
struct TYPE_15__ {int /*<<< orphan*/  pSrc; TYPE_7__* pEList; } ;
struct TYPE_13__ {int /*<<< orphan*/  pExpr; } ;
typedef  TYPE_4__ Select ;
typedef  TYPE_5__ Parse ;
typedef  TYPE_6__ NameContext ;
typedef  TYPE_7__ ExprList ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int NC_AllowAgg ; 
 int NC_UEList ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int sqlite3ExprCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3ExprIsInteger (int /*<<< orphan*/ *,int*) ; 
 int sqlite3ResolveExprNames (TYPE_6__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int resolveOrderByTermToExprList(
  Parse *pParse,     /* Parsing context for error messages */
  Select *pSelect,   /* The SELECT statement with the ORDER BY clause */
  Expr *pE           /* The specific ORDER BY term */
){
  int i;             /* Loop counter */
  ExprList *pEList;  /* The columns of the result set */
  NameContext nc;    /* Name context for resolving pE */
  sqlite3 *db;       /* Database connection */
  int rc;            /* Return code from subprocedures */
  u8 savedSuppErr;   /* Saved value of db->suppressErr */

  assert( sqlite3ExprIsInteger(pE, &i)==0 );
  pEList = pSelect->pEList;

  /* Resolve all names in the ORDER BY term expression
  */
  memset(&nc, 0, sizeof(nc));
  nc.pParse = pParse;
  nc.pSrcList = pSelect->pSrc;
  nc.uNC.pEList = pEList;
  nc.ncFlags = NC_AllowAgg|NC_UEList;
  nc.nErr = 0;
  db = pParse->db;
  savedSuppErr = db->suppressErr;
  db->suppressErr = 1;
  rc = sqlite3ResolveExprNames(&nc, pE);
  db->suppressErr = savedSuppErr;
  if( rc ) return 0;

  /* Try to match the ORDER BY expression against an expression
  ** in the result set.  Return an 1-based index of the matching
  ** result-set entry.
  */
  for(i=0; i<pEList->nExpr; i++){
    if( sqlite3ExprCompare(0, pEList->a[i].pExpr, pE, -1)<2 ){
      return i+1;
    }
  }

  /* If no match, return 0. */
  return 0;
}