#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_19__ ;
typedef  struct TYPE_36__   TYPE_12__ ;
typedef  struct TYPE_35__   TYPE_11__ ;
typedef  struct TYPE_34__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct SrcList_item {scalar_t__ iCursor; int /*<<< orphan*/  pTab; } ;
struct TYPE_42__ {TYPE_9__* pNC; } ;
struct TYPE_43__ {TYPE_8__* pParse; TYPE_5__ u; } ;
typedef  TYPE_6__ Walker ;
struct TYPE_46__ {int ncFlags; int nRef; struct TYPE_46__* pNext; TYPE_7__* pSrcList; int /*<<< orphan*/  nErr; TYPE_8__* pParse; } ;
struct TYPE_45__ {scalar_t__ nTab; TYPE_19__* db; scalar_t__ nErr; int /*<<< orphan*/  explain; } ;
struct TYPE_44__ {scalar_t__ nAlloc; int nSrc; struct SrcList_item* a; } ;
struct TYPE_41__ {TYPE_11__* pList; int /*<<< orphan*/  pSelect; } ;
struct TYPE_40__ {TYPE_12__* pExpr; } ;
struct TYPE_39__ {int /*<<< orphan*/  busy; } ;
struct TYPE_38__ {char* zToken; } ;
struct TYPE_37__ {scalar_t__ mallocFailed; TYPE_2__ init; } ;
struct TYPE_36__ {int op; int iTable; int iColumn; struct TYPE_36__* pRight; TYPE_4__ x; struct TYPE_36__* pLeft; int /*<<< orphan*/  op2; TYPE_1__ u; int /*<<< orphan*/  affinity; int /*<<< orphan*/  pTab; } ;
struct TYPE_35__ {int nExpr; TYPE_3__* a; } ;
struct TYPE_34__ {int funcFlags; unsigned char* zName; int /*<<< orphan*/  xFinalize; } ;
typedef  TYPE_7__ SrcList ;
typedef  TYPE_8__ Parse ;
typedef  TYPE_9__ NameContext ;
typedef  TYPE_10__ FuncDef ;
typedef  TYPE_11__ ExprList ;
typedef  TYPE_12__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  ENC (TYPE_19__*) ; 
 int EP_ConstFunc ; 
 int EP_Resolved ; 
 int EP_Skip ; 
 int EP_Unlikely ; 
 int EP_VarSelect ; 
 int EP_xIsSelect ; 
 scalar_t__ ExprHasProperty (TYPE_12__*,int) ; 
 int /*<<< orphan*/  ExprSetProperty (TYPE_12__*,int) ; 
 int NC_AllowAgg ; 
 int NC_HasAgg ; 
 int NC_IdxExpr ; 
 int NC_IsCheck ; 
 int NC_MinMaxAgg ; 
 int NC_PartIdx ; 
 int NC_VarSelect ; 
 int /*<<< orphan*/  SQLITE_AFF_INTEGER ; 
 int SQLITE_DENY ; 
 int /*<<< orphan*/  SQLITE_FUNCTION ; 
 int SQLITE_FUNC_CONSTANT ; 
 int SQLITE_FUNC_MINMAX ; 
 int SQLITE_FUNC_SLOCHNG ; 
 int SQLITE_FUNC_UNLIKELY ; 
 int SQLITE_OK ; 
 int const TK_AGG_FUNCTION ; 
#define  TK_BETWEEN 144 
 int TK_COLUMN ; 
#define  TK_DOT 143 
#define  TK_EQ 142 
#define  TK_EXISTS 141 
#define  TK_FUNCTION 140 
#define  TK_GE 139 
#define  TK_GT 138 
#define  TK_ID 137 
#define  TK_IN 136 
#define  TK_IS 135 
#define  TK_ISNOT 134 
#define  TK_LE 133 
#define  TK_LT 132 
#define  TK_NE 131 
 int const TK_NULL ; 
#define  TK_ROW 130 
#define  TK_SELECT 129 
#define  TK_VARIABLE 128 
 int WRC_Abort ; 
 int WRC_Continue ; 
 int WRC_Prune ; 
 int /*<<< orphan*/  assert (int) ; 
 int exprProbability (TYPE_12__*) ; 
 int lookupName (TYPE_8__*,char const*,char const*,char const*,TYPE_9__*,TYPE_12__*) ; 
 int /*<<< orphan*/  notValid (TYPE_8__*,TYPE_9__*,char*,int) ; 
 int sqlite3AuthCheck (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_8__*,char*,...) ; 
 int sqlite3ExprVectorSize (TYPE_12__*) ; 
 TYPE_10__* sqlite3FindFunction (TYPE_19__*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3FunctionUsesThisSrc (TYPE_12__*,TYPE_7__*) ; 
 int sqlite3Strlen30 (char const*) ; 
 int /*<<< orphan*/  sqlite3WalkExprList (TYPE_6__*,TYPE_11__*) ; 
 int /*<<< orphan*/  sqlite3WalkSelect (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int resolveExprStep(Walker *pWalker, Expr *pExpr){
  NameContext *pNC;
  Parse *pParse;

  pNC = pWalker->u.pNC;
  assert( pNC!=0 );
  pParse = pNC->pParse;
  assert( pParse==pWalker->pParse );

  if( ExprHasProperty(pExpr, EP_Resolved) ) return WRC_Prune;
  ExprSetProperty(pExpr, EP_Resolved);
#ifndef NDEBUG
  if( pNC->pSrcList && pNC->pSrcList->nAlloc>0 ){
    SrcList *pSrcList = pNC->pSrcList;
    int i;
    for(i=0; i<pNC->pSrcList->nSrc; i++){
      assert( pSrcList->a[i].iCursor>=0 && pSrcList->a[i].iCursor<pParse->nTab);
    }
  }
#endif
  switch( pExpr->op ){

#if defined(SQLITE_ENABLE_UPDATE_DELETE_LIMIT) && !defined(SQLITE_OMIT_SUBQUERY)
    /* The special operator TK_ROW means use the rowid for the first
    ** column in the FROM clause.  This is used by the LIMIT and ORDER BY
    ** clause processing on UPDATE and DELETE statements.
    */
    case TK_ROW: {
      SrcList *pSrcList = pNC->pSrcList;
      struct SrcList_item *pItem;
      assert( pSrcList && pSrcList->nSrc==1 );
      pItem = pSrcList->a;
      pExpr->op = TK_COLUMN;
      pExpr->pTab = pItem->pTab;
      pExpr->iTable = pItem->iCursor;
      pExpr->iColumn = -1;
      pExpr->affinity = SQLITE_AFF_INTEGER;
      break;
    }
#endif /* defined(SQLITE_ENABLE_UPDATE_DELETE_LIMIT)
          && !defined(SQLITE_OMIT_SUBQUERY) */

    /* A column name:                    ID
    ** Or table name and column name:    ID.ID
    ** Or a database, table and column:  ID.ID.ID
    **
    ** The TK_ID and TK_OUT cases are combined so that there will only
    ** be one call to lookupName().  Then the compiler will in-line
    ** lookupName() for a size reduction and performance increase.
    */
    case TK_ID:
    case TK_DOT: {
      const char *zColumn;
      const char *zTable;
      const char *zDb;
      Expr *pRight;

      if( pExpr->op==TK_ID ){
        zDb = 0;
        zTable = 0;
        zColumn = pExpr->u.zToken;
      }else{
        notValid(pParse, pNC, "the \".\" operator", NC_IdxExpr);
        pRight = pExpr->pRight;
        if( pRight->op==TK_ID ){
          zDb = 0;
          zTable = pExpr->pLeft->u.zToken;
          zColumn = pRight->u.zToken;
        }else{
          assert( pRight->op==TK_DOT );
          zDb = pExpr->pLeft->u.zToken;
          zTable = pRight->pLeft->u.zToken;
          zColumn = pRight->pRight->u.zToken;
        }
      }
      return lookupName(pParse, zDb, zTable, zColumn, pNC, pExpr);
    }

    /* Resolve function names
    */
    case TK_FUNCTION: {
      ExprList *pList = pExpr->x.pList;    /* The argument list */
      int n = pList ? pList->nExpr : 0;    /* Number of arguments */
      int no_such_func = 0;       /* True if no such function exists */
      int wrong_num_args = 0;     /* True if wrong number of arguments */
      int is_agg = 0;             /* True if is an aggregate function */
      int nId;                    /* Number of characters in function name */
      const char *zId;            /* The function name. */
      FuncDef *pDef;              /* Information about the function */
      u8 enc = ENC(pParse->db);   /* The database encoding */

      assert( !ExprHasProperty(pExpr, EP_xIsSelect) );
      zId = pExpr->u.zToken;
      nId = sqlite3Strlen30(zId);
      pDef = sqlite3FindFunction(pParse->db, zId, n, enc, 0);
      if( pDef==0 ){
        pDef = sqlite3FindFunction(pParse->db, zId, -2, enc, 0);
        if( pDef==0 ){
          no_such_func = 1;
        }else{
          wrong_num_args = 1;
        }
      }else{
        is_agg = pDef->xFinalize!=0;
        if( pDef->funcFlags & SQLITE_FUNC_UNLIKELY ){
          ExprSetProperty(pExpr, EP_Unlikely|EP_Skip);
          if( n==2 ){
            pExpr->iTable = exprProbability(pList->a[1].pExpr);
            if( pExpr->iTable<0 ){
              sqlite3ErrorMsg(pParse,
                "second argument to likelihood() must be a "
                "constant between 0.0 and 1.0");
              pNC->nErr++;
            }
          }else{
            /* EVIDENCE-OF: R-61304-29449 The unlikely(X) function is
            ** equivalent to likelihood(X, 0.0625).
            ** EVIDENCE-OF: R-01283-11636 The unlikely(X) function is
            ** short-hand for likelihood(X,0.0625).
            ** EVIDENCE-OF: R-36850-34127 The likely(X) function is short-hand
            ** for likelihood(X,0.9375).
            ** EVIDENCE-OF: R-53436-40973 The likely(X) function is equivalent
            ** to likelihood(X,0.9375). */
            /* TUNING: unlikely() probability is 0.0625.  likely() is 0.9375 */
            pExpr->iTable = pDef->zName[0]=='u' ? 8388608 : 125829120;
          }
        }
#ifndef SQLITE_OMIT_AUTHORIZATION
        {
          int auth = sqlite3AuthCheck(pParse, SQLITE_FUNCTION, 0,pDef->zName,0);
          if( auth!=SQLITE_OK ){
            if( auth==SQLITE_DENY ){
              sqlite3ErrorMsg(pParse, "not authorized to use function: %s",
                                      pDef->zName);
              pNC->nErr++;
            }
            pExpr->op = TK_NULL;
            return WRC_Prune;
          }
        }
#endif
        if( pDef->funcFlags & (SQLITE_FUNC_CONSTANT|SQLITE_FUNC_SLOCHNG) ){
          /* For the purposes of the EP_ConstFunc flag, date and time
          ** functions and other functions that change slowly are considered
          ** constant because they are constant for the duration of one query */
          ExprSetProperty(pExpr,EP_ConstFunc);
        }
        if( (pDef->funcFlags & SQLITE_FUNC_CONSTANT)==0 ){
          /* Date/time functions that use 'now', and other functions like
          ** sqlite_version() that might change over time cannot be used
          ** in an index. */
          notValid(pParse, pNC, "non-deterministic functions",
                   NC_IdxExpr|NC_PartIdx);
        }
      }
      if( is_agg && (pNC->ncFlags & NC_AllowAgg)==0 ){
        sqlite3ErrorMsg(pParse, "misuse of aggregate function %.*s()", nId,zId);
        pNC->nErr++;
        is_agg = 0;
      }else if( no_such_func && pParse->db->init.busy==0
#ifdef SQLITE_ENABLE_UNKNOWN_SQL_FUNCTION
                && pParse->explain==0
#endif
      ){
        sqlite3ErrorMsg(pParse, "no such function: %.*s", nId, zId);
        pNC->nErr++;
      }else if( wrong_num_args ){
        sqlite3ErrorMsg(pParse,"wrong number of arguments to function %.*s()",
             nId, zId);
        pNC->nErr++;
      }
      if( is_agg ) pNC->ncFlags &= ~NC_AllowAgg;
      sqlite3WalkExprList(pWalker, pList);
      if( is_agg ){
        NameContext *pNC2 = pNC;
        pExpr->op = TK_AGG_FUNCTION;
        pExpr->op2 = 0;
        while( pNC2 && !sqlite3FunctionUsesThisSrc(pExpr, pNC2->pSrcList) ){
          pExpr->op2++;
          pNC2 = pNC2->pNext;
        }
        assert( pDef!=0 );
        if( pNC2 ){
          assert( SQLITE_FUNC_MINMAX==NC_MinMaxAgg );
          testcase( (pDef->funcFlags & SQLITE_FUNC_MINMAX)!=0 );
          pNC2->ncFlags |= NC_HasAgg | (pDef->funcFlags & SQLITE_FUNC_MINMAX);

        }
        pNC->ncFlags |= NC_AllowAgg;
      }
      /* FIX ME:  Compute pExpr->affinity based on the expected return
      ** type of the function
      */
      return WRC_Prune;
    }
#ifndef SQLITE_OMIT_SUBQUERY
    case TK_SELECT:
    case TK_EXISTS:  testcase( pExpr->op==TK_EXISTS );
#endif
    case TK_IN: {
      testcase( pExpr->op==TK_IN );
      if( ExprHasProperty(pExpr, EP_xIsSelect) ){
        int nRef = pNC->nRef;
        notValid(pParse, pNC, "subqueries", NC_IsCheck|NC_PartIdx|NC_IdxExpr);
        sqlite3WalkSelect(pWalker, pExpr->x.pSelect);
        assert( pNC->nRef>=nRef );
        if( nRef!=pNC->nRef ){
          ExprSetProperty(pExpr, EP_VarSelect);
          pNC->ncFlags |= NC_VarSelect;
        }
      }
      break;
    }
    case TK_VARIABLE: {
      notValid(pParse, pNC, "parameters", NC_IsCheck|NC_PartIdx|NC_IdxExpr);
      break;
    }
    case TK_BETWEEN:
    case TK_EQ:
    case TK_NE:
    case TK_LT:
    case TK_LE:
    case TK_GT:
    case TK_GE:
    case TK_IS:
    case TK_ISNOT: {
      int nLeft, nRight;
      if( pParse->db->mallocFailed ) break;
      assert( pExpr->pLeft!=0 );
      nLeft = sqlite3ExprVectorSize(pExpr->pLeft);
      if( pExpr->op==TK_BETWEEN ){
        nRight = sqlite3ExprVectorSize(pExpr->x.pList->a[0].pExpr);
        if( nRight==nLeft ){
          nRight = sqlite3ExprVectorSize(pExpr->x.pList->a[1].pExpr);
        }
      }else{
        assert( pExpr->pRight!=0 );
        nRight = sqlite3ExprVectorSize(pExpr->pRight);
      }
      if( nLeft!=nRight ){
        testcase( pExpr->op==TK_EQ );
        testcase( pExpr->op==TK_NE );
        testcase( pExpr->op==TK_LT );
        testcase( pExpr->op==TK_LE );
        testcase( pExpr->op==TK_GT );
        testcase( pExpr->op==TK_GE );
        testcase( pExpr->op==TK_IS );
        testcase( pExpr->op==TK_ISNOT );
        testcase( pExpr->op==TK_BETWEEN );
        sqlite3ErrorMsg(pParse, "row value misused");
      }
      break;
    }
  }
  return (pParse->nErr || pParse->db->mallocFailed) ? WRC_Abort : WRC_Continue;
}