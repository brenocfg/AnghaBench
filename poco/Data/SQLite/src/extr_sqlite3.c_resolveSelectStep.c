#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_9__ ;
typedef  struct TYPE_47__   TYPE_8__ ;
typedef  struct TYPE_46__   TYPE_7__ ;
typedef  struct TYPE_45__   TYPE_6__ ;
typedef  struct TYPE_44__   TYPE_5__ ;
typedef  struct TYPE_43__   TYPE_4__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_24__ ;
typedef  struct TYPE_39__   TYPE_1__ ;
typedef  struct TYPE_38__   TYPE_15__ ;
typedef  struct TYPE_37__   TYPE_13__ ;
typedef  struct TYPE_36__   TYPE_12__ ;
typedef  struct TYPE_35__   TYPE_11__ ;
typedef  struct TYPE_34__   TYPE_10__ ;

/* Type definitions */
struct TYPE_42__ {TYPE_24__* pFuncArg; } ;
struct TYPE_41__ {int isCorrelated; scalar_t__ isTabFunc; } ;
struct SrcList_item {char* zName; TYPE_10__* pSelect; TYPE_3__ u1; TYPE_2__ fg; } ;
struct ExprList_item {int /*<<< orphan*/  pExpr; } ;
struct TYPE_46__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_7__ sqlite3 ;
typedef  int /*<<< orphan*/  sNC ;
struct TYPE_47__ {TYPE_24__* pPartition; TYPE_24__* pOrderBy; struct TYPE_47__* pNextWin; } ;
typedef  TYPE_8__ Window ;
struct TYPE_44__ {TYPE_12__* pNC; } ;
struct TYPE_48__ {TYPE_11__* pParse; TYPE_5__ u; } ;
typedef  TYPE_9__ Walker ;
struct TYPE_45__ {int nSrc; struct SrcList_item* a; } ;
struct TYPE_43__ {scalar_t__ nExpr; } ;
struct TYPE_40__ {scalar_t__ nExpr; } ;
struct TYPE_39__ {TYPE_24__* pEList; } ;
struct TYPE_38__ {TYPE_4__* pEList; } ;
struct TYPE_37__ {int nExpr; struct ExprList_item* a; } ;
struct TYPE_36__ {int ncFlags; struct TYPE_36__* pNext; TYPE_1__ uNC; TYPE_6__* pSrcList; scalar_t__ nRef; TYPE_10__* pWinSelect; TYPE_11__* pParse; } ;
struct TYPE_35__ {char* zAuthContext; scalar_t__ nErr; TYPE_7__* db; } ;
struct TYPE_34__ {int selFlags; scalar_t__ pOrderBy; struct TYPE_34__* pPrior; TYPE_15__* pNext; TYPE_24__* pEList; TYPE_8__* pWinDefn; TYPE_6__* pSrc; int /*<<< orphan*/  pWhere; int /*<<< orphan*/  pHaving; TYPE_13__* pGroupBy; int /*<<< orphan*/  pLimit; } ;
typedef  TYPE_10__ Select ;
typedef  TYPE_11__ Parse ;
typedef  TYPE_12__ NameContext ;
typedef  TYPE_13__ ExprList ;

/* Variables and functions */
 int /*<<< orphan*/  EP_Agg ; 
 scalar_t__ ExprHasProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IN_RENAME_OBJECT ; 
 int NC_AllowAgg ; 
 int NC_AllowWin ; 
 int NC_HasAgg ; 
 int NC_MinMaxAgg ; 
 int NC_UAggInfo ; 
 int NC_UEList ; 
 int NC_UUpsert ; 
 int SF_Aggregate ; 
 int SF_Converted ; 
 int SF_Expanded ; 
 int SF_MinMaxAgg ; 
 int SF_Resolved ; 
 int WRC_Abort ; 
 int WRC_Prune ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_12__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ resolveCompoundOrderBy (TYPE_11__*,TYPE_10__*) ; 
 scalar_t__ resolveOrderGroupBy (TYPE_12__*,TYPE_10__*,TYPE_13__*,char*) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_11__*,char*) ; 
 scalar_t__ sqlite3ResolveExprListNames (TYPE_12__*,TYPE_24__*) ; 
 scalar_t__ sqlite3ResolveExprNames (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ResolveSelectNames (TYPE_11__*,TYPE_10__*,TYPE_12__*) ; 
 int /*<<< orphan*/  sqlite3SelectPrep (TYPE_11__*,TYPE_10__*,TYPE_12__*) ; 
 int /*<<< orphan*/  sqlite3SelectWrongNumTermsError (TYPE_11__*,TYPE_15__*) ; 

__attribute__((used)) static int resolveSelectStep(Walker *pWalker, Select *p){
  NameContext *pOuterNC;  /* Context that contains this SELECT */
  NameContext sNC;        /* Name context of this SELECT */
  int isCompound;         /* True if p is a compound select */
  int nCompound;          /* Number of compound terms processed so far */
  Parse *pParse;          /* Parsing context */
  int i;                  /* Loop counter */
  ExprList *pGroupBy;     /* The GROUP BY clause */
  Select *pLeftmost;      /* Left-most of SELECT of a compound */
  sqlite3 *db;            /* Database connection */
  

  assert( p!=0 );
  if( p->selFlags & SF_Resolved ){
    return WRC_Prune;
  }
  pOuterNC = pWalker->u.pNC;
  pParse = pWalker->pParse;
  db = pParse->db;

  /* Normally sqlite3SelectExpand() will be called first and will have
  ** already expanded this SELECT.  However, if this is a subquery within
  ** an expression, sqlite3ResolveExprNames() will be called without a
  ** prior call to sqlite3SelectExpand().  When that happens, let
  ** sqlite3SelectPrep() do all of the processing for this SELECT.
  ** sqlite3SelectPrep() will invoke both sqlite3SelectExpand() and
  ** this routine in the correct order.
  */
  if( (p->selFlags & SF_Expanded)==0 ){
    sqlite3SelectPrep(pParse, p, pOuterNC);
    return (pParse->nErr || db->mallocFailed) ? WRC_Abort : WRC_Prune;
  }

  isCompound = p->pPrior!=0;
  nCompound = 0;
  pLeftmost = p;
  while( p ){
    assert( (p->selFlags & SF_Expanded)!=0 );
    assert( (p->selFlags & SF_Resolved)==0 );
    p->selFlags |= SF_Resolved;

    /* Resolve the expressions in the LIMIT and OFFSET clauses. These
    ** are not allowed to refer to any names, so pass an empty NameContext.
    */
    memset(&sNC, 0, sizeof(sNC));
    sNC.pParse = pParse;
    sNC.pWinSelect = p;
    if( sqlite3ResolveExprNames(&sNC, p->pLimit) ){
      return WRC_Abort;
    }

    /* If the SF_Converted flags is set, then this Select object was
    ** was created by the convertCompoundSelectToSubquery() function.
    ** In this case the ORDER BY clause (p->pOrderBy) should be resolved
    ** as if it were part of the sub-query, not the parent. This block
    ** moves the pOrderBy down to the sub-query. It will be moved back
    ** after the names have been resolved.  */
    if( p->selFlags & SF_Converted ){
      Select *pSub = p->pSrc->a[0].pSelect;
      assert( p->pSrc->nSrc==1 && p->pOrderBy );
      assert( pSub->pPrior && pSub->pOrderBy==0 );
      pSub->pOrderBy = p->pOrderBy;
      p->pOrderBy = 0;
    }
  
    /* Recursively resolve names in all subqueries
    */
    for(i=0; i<p->pSrc->nSrc; i++){
      struct SrcList_item *pItem = &p->pSrc->a[i];
      if( pItem->pSelect && (pItem->pSelect->selFlags & SF_Resolved)==0 ){
        NameContext *pNC;         /* Used to iterate name contexts */
        int nRef = 0;             /* Refcount for pOuterNC and outer contexts */
        const char *zSavedContext = pParse->zAuthContext;

        /* Count the total number of references to pOuterNC and all of its
        ** parent contexts. After resolving references to expressions in
        ** pItem->pSelect, check if this value has changed. If so, then
        ** SELECT statement pItem->pSelect must be correlated. Set the
        ** pItem->fg.isCorrelated flag if this is the case. */
        for(pNC=pOuterNC; pNC; pNC=pNC->pNext) nRef += pNC->nRef;

        if( pItem->zName ) pParse->zAuthContext = pItem->zName;
        sqlite3ResolveSelectNames(pParse, pItem->pSelect, pOuterNC);
        pParse->zAuthContext = zSavedContext;
        if( pParse->nErr || db->mallocFailed ) return WRC_Abort;

        for(pNC=pOuterNC; pNC; pNC=pNC->pNext) nRef -= pNC->nRef;
        assert( pItem->fg.isCorrelated==0 && nRef<=0 );
        pItem->fg.isCorrelated = (nRef!=0);
      }
    }
  
    /* Set up the local name-context to pass to sqlite3ResolveExprNames() to
    ** resolve the result-set expression list.
    */
    sNC.ncFlags = NC_AllowAgg|NC_AllowWin;
    sNC.pSrcList = p->pSrc;
    sNC.pNext = pOuterNC;
  
    /* Resolve names in the result set. */
    if( sqlite3ResolveExprListNames(&sNC, p->pEList) ) return WRC_Abort;
    sNC.ncFlags &= ~NC_AllowWin;
  
    /* If there are no aggregate functions in the result-set, and no GROUP BY 
    ** expression, do not allow aggregates in any of the other expressions.
    */
    assert( (p->selFlags & SF_Aggregate)==0 );
    pGroupBy = p->pGroupBy;
    if( pGroupBy || (sNC.ncFlags & NC_HasAgg)!=0 ){
      assert( NC_MinMaxAgg==SF_MinMaxAgg );
      p->selFlags |= SF_Aggregate | (sNC.ncFlags&NC_MinMaxAgg);
    }else{
      sNC.ncFlags &= ~NC_AllowAgg;
    }
  
    /* If a HAVING clause is present, then there must be a GROUP BY clause.
    */
    if( p->pHaving && !pGroupBy ){
      sqlite3ErrorMsg(pParse, "a GROUP BY clause is required before HAVING");
      return WRC_Abort;
    }
  
    /* Add the output column list to the name-context before parsing the
    ** other expressions in the SELECT statement. This is so that
    ** expressions in the WHERE clause (etc.) can refer to expressions by
    ** aliases in the result set.
    **
    ** Minor point: If this is the case, then the expression will be
    ** re-evaluated for each reference to it.
    */
    assert( (sNC.ncFlags & (NC_UAggInfo|NC_UUpsert))==0 );
    sNC.uNC.pEList = p->pEList;
    sNC.ncFlags |= NC_UEList;
    if( sqlite3ResolveExprNames(&sNC, p->pHaving) ) return WRC_Abort;
    if( sqlite3ResolveExprNames(&sNC, p->pWhere) ) return WRC_Abort;

    /* Resolve names in table-valued-function arguments */
    for(i=0; i<p->pSrc->nSrc; i++){
      struct SrcList_item *pItem = &p->pSrc->a[i];
      if( pItem->fg.isTabFunc
       && sqlite3ResolveExprListNames(&sNC, pItem->u1.pFuncArg) 
      ){
        return WRC_Abort;
      }
    }

    /* The ORDER BY and GROUP BY clauses may not refer to terms in
    ** outer queries 
    */
    sNC.pNext = 0;
    sNC.ncFlags |= NC_AllowAgg|NC_AllowWin;

    /* If this is a converted compound query, move the ORDER BY clause from 
    ** the sub-query back to the parent query. At this point each term
    ** within the ORDER BY clause has been transformed to an integer value.
    ** These integers will be replaced by copies of the corresponding result
    ** set expressions by the call to resolveOrderGroupBy() below.  */
    if( p->selFlags & SF_Converted ){
      Select *pSub = p->pSrc->a[0].pSelect;
      p->pOrderBy = pSub->pOrderBy;
      pSub->pOrderBy = 0;
    }

    /* Process the ORDER BY clause for singleton SELECT statements.
    ** The ORDER BY clause for compounds SELECT statements is handled
    ** below, after all of the result-sets for all of the elements of
    ** the compound have been resolved.
    **
    ** If there is an ORDER BY clause on a term of a compound-select other
    ** than the right-most term, then that is a syntax error.  But the error
    ** is not detected until much later, and so we need to go ahead and
    ** resolve those symbols on the incorrect ORDER BY for consistency.
    */
    if( isCompound<=nCompound  /* Defer right-most ORDER BY of a compound */
     && resolveOrderGroupBy(&sNC, p, p->pOrderBy, "ORDER")
    ){
      return WRC_Abort;
    }
    if( db->mallocFailed ){
      return WRC_Abort;
    }
    sNC.ncFlags &= ~NC_AllowWin;
  
    /* Resolve the GROUP BY clause.  At the same time, make sure 
    ** the GROUP BY clause does not contain aggregate functions.
    */
    if( pGroupBy ){
      struct ExprList_item *pItem;
    
      if( resolveOrderGroupBy(&sNC, p, pGroupBy, "GROUP") || db->mallocFailed ){
        return WRC_Abort;
      }
      for(i=0, pItem=pGroupBy->a; i<pGroupBy->nExpr; i++, pItem++){
        if( ExprHasProperty(pItem->pExpr, EP_Agg) ){
          sqlite3ErrorMsg(pParse, "aggregate functions are not allowed in "
              "the GROUP BY clause");
          return WRC_Abort;
        }
      }
    }

#ifndef SQLITE_OMIT_WINDOWFUNC
    if( IN_RENAME_OBJECT ){
      Window *pWin;
      for(pWin=p->pWinDefn; pWin; pWin=pWin->pNextWin){
        if( sqlite3ResolveExprListNames(&sNC, pWin->pOrderBy)
         || sqlite3ResolveExprListNames(&sNC, pWin->pPartition)
        ){
          return WRC_Abort;
        }
      }
    }
#endif

    /* If this is part of a compound SELECT, check that it has the right
    ** number of expressions in the select list. */
    if( p->pNext && p->pEList->nExpr!=p->pNext->pEList->nExpr ){
      sqlite3SelectWrongNumTermsError(pParse, p->pNext);
      return WRC_Abort;
    }

    /* Advance to the next term of the compound
    */
    p = p->pPrior;
    nCompound++;
  }

  /* Resolve the ORDER BY on a compound SELECT after all terms of
  ** the compound have been resolved.
  */
  if( isCompound && resolveCompoundOrderBy(pParse, pLeftmost) ){
    return WRC_Abort;
  }

  return WRC_Prune;
}