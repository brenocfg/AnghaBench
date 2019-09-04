#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct SrcList_item {char* zName; int isCorrelated; scalar_t__ pSelect; } ;
struct ExprList_item {int /*<<< orphan*/ * pExpr; } ;
struct TYPE_26__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_3__ sqlite3 ;
typedef  int /*<<< orphan*/  sNC ;
struct TYPE_24__ {TYPE_7__* pNC; } ;
struct TYPE_27__ {TYPE_6__* pParse; TYPE_1__ u; } ;
typedef  TYPE_4__ Walker ;
struct TYPE_31__ {int nExpr; struct ExprList_item* a; } ;
struct TYPE_30__ {int ncFlags; struct TYPE_30__* pNext; TYPE_8__* pEList; TYPE_2__* pSrcList; scalar_t__ nRef; TYPE_6__* pParse; } ;
struct TYPE_29__ {char* zAuthContext; scalar_t__ nErr; TYPE_3__* db; } ;
struct TYPE_28__ {int selFlags; struct TYPE_28__* pPrior; TYPE_8__* pOrderBy; int /*<<< orphan*/ * pWhere; int /*<<< orphan*/ * pHaving; TYPE_8__* pEList; TYPE_8__* pGroupBy; TYPE_2__* pSrc; int /*<<< orphan*/ * pOffset; int /*<<< orphan*/ * pLimit; } ;
struct TYPE_25__ {int nSrc; struct SrcList_item* a; } ;
typedef  TYPE_5__ Select ;
typedef  TYPE_6__ Parse ;
typedef  TYPE_7__ NameContext ;
typedef  TYPE_8__ ExprList ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_Agg ; 
 scalar_t__ ExprHasProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NC_AllowAgg ; 
 int NC_AsMaybe ; 
 int NC_HasAgg ; 
 int SF_Aggregate ; 
 int SF_Expanded ; 
 int SF_Resolved ; 
 int WRC_Abort ; 
 int WRC_Prune ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ resolveCompoundOrderBy (TYPE_6__*,TYPE_5__*) ; 
 scalar_t__ resolveOrderGroupBy (TYPE_7__*,TYPE_5__*,TYPE_8__*,char*) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_6__*,char*) ; 
 scalar_t__ sqlite3ResolveExprNames (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3ResolveSelectNames (TYPE_6__*,scalar_t__,TYPE_7__*) ; 
 int /*<<< orphan*/  sqlite3SelectPrep (TYPE_6__*,TYPE_5__*,TYPE_7__*) ; 

__attribute__((used)) static int resolveSelectStep(Walker *pWalker, Select *p){
  NameContext *pOuterNC;  /* Context that contains this SELECT */
  NameContext sNC;        /* Name context of this SELECT */
  int isCompound;         /* True if p is a compound select */
  int nCompound;          /* Number of compound terms processed so far */
  Parse *pParse;          /* Parsing context */
  ExprList *pEList;       /* Result set expression list */
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
    if( sqlite3ResolveExprNames(&sNC, p->pLimit) ||
        sqlite3ResolveExprNames(&sNC, p->pOffset) ){
      return WRC_Abort;
    }
  
    /* Recursively resolve names in all subqueries
    */
    for(i=0; i<p->pSrc->nSrc; i++){
      struct SrcList_item *pItem = &p->pSrc->a[i];
      if( pItem->pSelect ){
        NameContext *pNC;         /* Used to iterate name contexts */
        int nRef = 0;             /* Refcount for pOuterNC and outer contexts */
        const char *zSavedContext = pParse->zAuthContext;

        /* Count the total number of references to pOuterNC and all of its
        ** parent contexts. After resolving references to expressions in
        ** pItem->pSelect, check if this value has changed. If so, then
        ** SELECT statement pItem->pSelect must be correlated. Set the
        ** pItem->isCorrelated flag if this is the case. */
        for(pNC=pOuterNC; pNC; pNC=pNC->pNext) nRef += pNC->nRef;

        if( pItem->zName ) pParse->zAuthContext = pItem->zName;
        sqlite3ResolveSelectNames(pParse, pItem->pSelect, pOuterNC);
        pParse->zAuthContext = zSavedContext;
        if( pParse->nErr || db->mallocFailed ) return WRC_Abort;

        for(pNC=pOuterNC; pNC; pNC=pNC->pNext) nRef -= pNC->nRef;
        assert( pItem->isCorrelated==0 && nRef<=0 );
        pItem->isCorrelated = (nRef!=0);
      }
    }
  
    /* Set up the local name-context to pass to sqlite3ResolveExprNames() to
    ** resolve the result-set expression list.
    */
    sNC.ncFlags = NC_AllowAgg;
    sNC.pSrcList = p->pSrc;
    sNC.pNext = pOuterNC;
  
    /* Resolve names in the result set. */
    pEList = p->pEList;
    assert( pEList!=0 );
    for(i=0; i<pEList->nExpr; i++){
      Expr *pX = pEList->a[i].pExpr;
      if( sqlite3ResolveExprNames(&sNC, pX) ){
        return WRC_Abort;
      }
    }
  
    /* If there are no aggregate functions in the result-set, and no GROUP BY 
    ** expression, do not allow aggregates in any of the other expressions.
    */
    assert( (p->selFlags & SF_Aggregate)==0 );
    pGroupBy = p->pGroupBy;
    if( pGroupBy || (sNC.ncFlags & NC_HasAgg)!=0 ){
      p->selFlags |= SF_Aggregate;
    }else{
      sNC.ncFlags &= ~NC_AllowAgg;
    }
  
    /* If a HAVING clause is present, then there must be a GROUP BY clause.
    */
    if( p->pHaving && !pGroupBy ){
      sqlite3ErrorMsg(pParse, "a GROUP BY clause is required before HAVING");
      return WRC_Abort;
    }
  
    /* Add the expression list to the name-context before parsing the
    ** other expressions in the SELECT statement. This is so that
    ** expressions in the WHERE clause (etc.) can refer to expressions by
    ** aliases in the result set.
    **
    ** Minor point: If this is the case, then the expression will be
    ** re-evaluated for each reference to it.
    */
    sNC.pEList = p->pEList;
    sNC.ncFlags |= NC_AsMaybe;
    if( sqlite3ResolveExprNames(&sNC, p->pHaving) ) return WRC_Abort;
    if( sqlite3ResolveExprNames(&sNC, p->pWhere) ) return WRC_Abort;
    sNC.ncFlags &= ~NC_AsMaybe;

    /* The ORDER BY and GROUP BY clauses may not refer to terms in
    ** outer queries 
    */
    sNC.pNext = 0;
    sNC.ncFlags |= NC_AllowAgg;

    /* Process the ORDER BY clause for singleton SELECT statements.
    ** The ORDER BY clause for compounds SELECT statements is handled
    ** below, after all of the result-sets for all of the elements of
    ** the compound have been resolved.
    */
    if( !isCompound && resolveOrderGroupBy(&sNC, p, p->pOrderBy, "ORDER") ){
      return WRC_Abort;
    }
    if( db->mallocFailed ){
      return WRC_Abort;
    }
  
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