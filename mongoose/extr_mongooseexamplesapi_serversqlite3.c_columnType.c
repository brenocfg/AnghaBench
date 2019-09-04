#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_28__ {int pSchema; int iPKey; int nCol; char* zName; TYPE_2__* aCol; } ;
typedef  TYPE_8__ Table ;
struct TYPE_29__ {int nSrc; TYPE_1__* a; } ;
struct TYPE_27__ {TYPE_13__* db; } ;
struct TYPE_26__ {int nExpr; TYPE_5__* a; } ;
struct TYPE_25__ {TYPE_12__* pExpr; } ;
struct TYPE_24__ {TYPE_10__* pSelect; } ;
struct TYPE_23__ {char* zName; } ;
struct TYPE_22__ {char* zType; char* zName; } ;
struct TYPE_21__ {TYPE_10__* pSelect; TYPE_8__* pTab; int /*<<< orphan*/  iCursor; } ;
struct TYPE_20__ {TYPE_3__* aDb; } ;
struct TYPE_19__ {int op; int iColumn; TYPE_4__ x; TYPE_8__* pTab; int /*<<< orphan*/  iTable; } ;
struct TYPE_18__ {scalar_t__ pSrcList; TYPE_7__* pParse; struct TYPE_18__* pNext; } ;
struct TYPE_17__ {TYPE_9__* pSrc; TYPE_6__* pEList; } ;
typedef  TYPE_9__ SrcList ;
typedef  TYPE_10__ Select ;
typedef  TYPE_11__ NameContext ;
typedef  TYPE_12__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  ALWAYS (int) ; 
 int /*<<< orphan*/  EP_xIsSelect ; 
 int ExprHasProperty (TYPE_12__*,int /*<<< orphan*/ ) ; 
 scalar_t__ NEVER (int) ; 
#define  TK_AGG_COLUMN 130 
#define  TK_COLUMN 129 
#define  TK_SELECT 128 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3SchemaToIndex (TYPE_13__*,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static const char *columnType(
  NameContext *pNC, 
  Expr *pExpr,
  const char **pzOriginDb,
  const char **pzOriginTab,
  const char **pzOriginCol
){
  char const *zType = 0;
  char const *zOriginDb = 0;
  char const *zOriginTab = 0;
  char const *zOriginCol = 0;
  int j;
  if( NEVER(pExpr==0) || pNC->pSrcList==0 ) return 0;

  switch( pExpr->op ){
    case TK_AGG_COLUMN:
    case TK_COLUMN: {
      /* The expression is a column. Locate the table the column is being
      ** extracted from in NameContext.pSrcList. This table may be real
      ** database table or a subquery.
      */
      Table *pTab = 0;            /* Table structure column is extracted from */
      Select *pS = 0;             /* Select the column is extracted from */
      int iCol = pExpr->iColumn;  /* Index of column in pTab */
      testcase( pExpr->op==TK_AGG_COLUMN );
      testcase( pExpr->op==TK_COLUMN );
      while( pNC && !pTab ){
        SrcList *pTabList = pNC->pSrcList;
        for(j=0;j<pTabList->nSrc && pTabList->a[j].iCursor!=pExpr->iTable;j++);
        if( j<pTabList->nSrc ){
          pTab = pTabList->a[j].pTab;
          pS = pTabList->a[j].pSelect;
        }else{
          pNC = pNC->pNext;
        }
      }

      if( pTab==0 ){
        /* At one time, code such as "SELECT new.x" within a trigger would
        ** cause this condition to run.  Since then, we have restructured how
        ** trigger code is generated and so this condition is no longer 
        ** possible. However, it can still be true for statements like
        ** the following:
        **
        **   CREATE TABLE t1(col INTEGER);
        **   SELECT (SELECT t1.col) FROM FROM t1;
        **
        ** when columnType() is called on the expression "t1.col" in the 
        ** sub-select. In this case, set the column type to NULL, even
        ** though it should really be "INTEGER".
        **
        ** This is not a problem, as the column type of "t1.col" is never
        ** used. When columnType() is called on the expression 
        ** "(SELECT t1.col)", the correct type is returned (see the TK_SELECT
        ** branch below.  */
        break;
      }

      assert( pTab && pExpr->pTab==pTab );
      if( pS ){
        /* The "table" is actually a sub-select or a view in the FROM clause
        ** of the SELECT statement. Return the declaration type and origin
        ** data for the result-set column of the sub-select.
        */
        if( iCol>=0 && ALWAYS(iCol<pS->pEList->nExpr) ){
          /* If iCol is less than zero, then the expression requests the
          ** rowid of the sub-select or view. This expression is legal (see 
          ** test case misc2.2.2) - it always evaluates to NULL.
          */
          NameContext sNC;
          Expr *p = pS->pEList->a[iCol].pExpr;
          sNC.pSrcList = pS->pSrc;
          sNC.pNext = pNC;
          sNC.pParse = pNC->pParse;
          zType = columnType(&sNC, p, &zOriginDb, &zOriginTab, &zOriginCol); 
        }
      }else if( ALWAYS(pTab->pSchema) ){
        /* A real table */
        assert( !pS );
        if( iCol<0 ) iCol = pTab->iPKey;
        assert( iCol==-1 || (iCol>=0 && iCol<pTab->nCol) );
        if( iCol<0 ){
          zType = "INTEGER";
          zOriginCol = "rowid";
        }else{
          zType = pTab->aCol[iCol].zType;
          zOriginCol = pTab->aCol[iCol].zName;
        }
        zOriginTab = pTab->zName;
        if( pNC->pParse ){
          int iDb = sqlite3SchemaToIndex(pNC->pParse->db, pTab->pSchema);
          zOriginDb = pNC->pParse->db->aDb[iDb].zName;
        }
      }
      break;
    }
#ifndef SQLITE_OMIT_SUBQUERY
    case TK_SELECT: {
      /* The expression is a sub-select. Return the declaration type and
      ** origin info for the single column in the result set of the SELECT
      ** statement.
      */
      NameContext sNC;
      Select *pS = pExpr->x.pSelect;
      Expr *p = pS->pEList->a[0].pExpr;
      assert( ExprHasProperty(pExpr, EP_xIsSelect) );
      sNC.pSrcList = pS->pSrc;
      sNC.pNext = pNC;
      sNC.pParse = pNC->pParse;
      zType = columnType(&sNC, p, &zOriginDb, &zOriginTab, &zOriginCol); 
      break;
    }
#endif
  }
  
  if( pzOriginDb ){
    assert( pzOriginTab && pzOriginCol );
    *pzOriginDb = zOriginDb;
    *pzOriginTab = zOriginTab;
    *pzOriginCol = zOriginCol;
  }
  return zType;
}