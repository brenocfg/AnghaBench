#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int flags; scalar_t__ mallocFailed; } ;
typedef  TYPE_4__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_22__ {int iPKey; int nCol; int /*<<< orphan*/  zName; TYPE_2__* aCol; } ;
typedef  TYPE_5__ Table ;
struct TYPE_26__ {scalar_t__ op; int iColumn; scalar_t__ iTable; } ;
struct TYPE_25__ {int nExpr; TYPE_3__* a; } ;
struct TYPE_24__ {int colNamesSet; scalar_t__ explain; TYPE_4__* db; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_23__ {int nSrc; TYPE_1__* a; } ;
struct TYPE_20__ {char* zName; int /*<<< orphan*/  zSpan; TYPE_9__* pExpr; } ;
struct TYPE_19__ {char* zName; } ;
struct TYPE_18__ {scalar_t__ iCursor; TYPE_5__* pTab; } ;
typedef  TYPE_6__ SrcList ;
typedef  TYPE_7__ Parse ;
typedef  TYPE_8__ ExprList ;
typedef  TYPE_9__ Expr ;

/* Variables and functions */
 scalar_t__ ALWAYS (int) ; 
 int /*<<< orphan*/  COLNAME_NAME ; 
 scalar_t__ NEVER (int) ; 
 int /*<<< orphan*/  SQLITE_DYNAMIC ; 
 int SQLITE_FullColNames ; 
 int SQLITE_ShortColNames ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 scalar_t__ TK_AGG_COLUMN ; 
 scalar_t__ TK_COLUMN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  generateColumnTypes (TYPE_7__*,TYPE_6__*,TYPE_8__*) ; 
 char* sqlite3DbStrDup (TYPE_4__*,int /*<<< orphan*/ ) ; 
 char* sqlite3MPrintf (TYPE_4__*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sqlite3VdbeSetColName (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeSetNumCols (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void generateColumnNames(
  Parse *pParse,      /* Parser context */
  SrcList *pTabList,  /* List of tables */
  ExprList *pEList    /* Expressions defining the result set */
){
  Vdbe *v = pParse->pVdbe;
  int i, j;
  sqlite3 *db = pParse->db;
  int fullNames, shortNames;

#ifndef SQLITE_OMIT_EXPLAIN
  /* If this is an EXPLAIN, skip this step */
  if( pParse->explain ){
    return;
  }
#endif

  if( pParse->colNamesSet || NEVER(v==0) || db->mallocFailed ) return;
  pParse->colNamesSet = 1;
  fullNames = (db->flags & SQLITE_FullColNames)!=0;
  shortNames = (db->flags & SQLITE_ShortColNames)!=0;
  sqlite3VdbeSetNumCols(v, pEList->nExpr);
  for(i=0; i<pEList->nExpr; i++){
    Expr *p;
    p = pEList->a[i].pExpr;
    if( NEVER(p==0) ) continue;
    if( pEList->a[i].zName ){
      char *zName = pEList->a[i].zName;
      sqlite3VdbeSetColName(v, i, COLNAME_NAME, zName, SQLITE_TRANSIENT);
    }else if( (p->op==TK_COLUMN || p->op==TK_AGG_COLUMN) && pTabList ){
      Table *pTab;
      char *zCol;
      int iCol = p->iColumn;
      for(j=0; ALWAYS(j<pTabList->nSrc); j++){
        if( pTabList->a[j].iCursor==p->iTable ) break;
      }
      assert( j<pTabList->nSrc );
      pTab = pTabList->a[j].pTab;
      if( iCol<0 ) iCol = pTab->iPKey;
      assert( iCol==-1 || (iCol>=0 && iCol<pTab->nCol) );
      if( iCol<0 ){
        zCol = "rowid";
      }else{
        zCol = pTab->aCol[iCol].zName;
      }
      if( !shortNames && !fullNames ){
        sqlite3VdbeSetColName(v, i, COLNAME_NAME, 
            sqlite3DbStrDup(db, pEList->a[i].zSpan), SQLITE_DYNAMIC);
      }else if( fullNames ){
        char *zName = 0;
        zName = sqlite3MPrintf(db, "%s.%s", pTab->zName, zCol);
        sqlite3VdbeSetColName(v, i, COLNAME_NAME, zName, SQLITE_DYNAMIC);
      }else{
        sqlite3VdbeSetColName(v, i, COLNAME_NAME, zCol, SQLITE_TRANSIENT);
      }
    }else{
      sqlite3VdbeSetColName(v, i, COLNAME_NAME, 
          sqlite3DbStrDup(db, pEList->a[i].zSpan), SQLITE_DYNAMIC);
    }
  }
  generateColumnTypes(pParse, pTabList, pEList);
}