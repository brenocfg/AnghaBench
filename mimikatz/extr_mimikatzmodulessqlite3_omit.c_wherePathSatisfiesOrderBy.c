#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_55__   TYPE_9__ ;
typedef  struct TYPE_54__   TYPE_8__ ;
typedef  struct TYPE_53__   TYPE_7__ ;
typedef  struct TYPE_52__   TYPE_6__ ;
typedef  struct TYPE_51__   TYPE_5__ ;
typedef  struct TYPE_50__   TYPE_4__ ;
typedef  struct TYPE_49__   TYPE_3__ ;
typedef  struct TYPE_48__   TYPE_36__ ;
typedef  struct TYPE_47__   TYPE_2__ ;
typedef  struct TYPE_46__   TYPE_27__ ;
typedef  struct TYPE_45__   TYPE_1__ ;
typedef  struct TYPE_44__   TYPE_17__ ;
typedef  struct TYPE_43__   TYPE_16__ ;
typedef  struct TYPE_42__   TYPE_15__ ;
typedef  struct TYPE_41__   TYPE_14__ ;
typedef  struct TYPE_40__   TYPE_13__ ;
typedef  struct TYPE_39__   TYPE_12__ ;
typedef  struct TYPE_38__   TYPE_11__ ;
typedef  struct TYPE_37__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int i8 ;
struct TYPE_37__ {int eOperator; TYPE_16__* pExpr; } ;
typedef  TYPE_10__ WhereTerm ;
struct TYPE_38__ {TYPE_12__** aLoop; } ;
typedef  TYPE_11__ WherePath ;
struct TYPE_53__ {int nIdxCol; int nEq; TYPE_14__* pIndex; } ;
struct TYPE_45__ {scalar_t__ isOrdered; } ;
struct TYPE_54__ {TYPE_7__ btree; TYPE_1__ vtab; } ;
struct TYPE_39__ {int maskSelf; int wsFlags; size_t iTab; int nLTerm; int nSkip; TYPE_8__ u; TYPE_10__** aLTerm; } ;
typedef  TYPE_12__ WhereLoop ;
struct TYPE_40__ {int /*<<< orphan*/  sMaskSet; TYPE_27__* pParse; int /*<<< orphan*/  sWC; TYPE_3__* pTabList; } ;
typedef  TYPE_13__ WhereInfo ;
struct TYPE_55__ {int sortOrder; TYPE_16__* pExpr; } ;
struct TYPE_52__ {TYPE_5__* a; } ;
struct TYPE_51__ {TYPE_16__* pExpr; } ;
struct TYPE_50__ {scalar_t__ notNull; } ;
struct TYPE_49__ {TYPE_2__* a; } ;
struct TYPE_48__ {int iPKey; TYPE_4__* aCol; } ;
struct TYPE_47__ {int iCursor; } ;
struct TYPE_46__ {int /*<<< orphan*/ * db; } ;
struct TYPE_44__ {int /*<<< orphan*/  zName; } ;
struct TYPE_43__ {scalar_t__ op; int iTable; int iColumn; } ;
struct TYPE_42__ {int nExpr; TYPE_9__* a; } ;
struct TYPE_41__ {int nKeyCol; int nColumn; int* aiColumn; int* aSortOrder; int /*<<< orphan*/ * azColl; TYPE_6__* aColExpr; TYPE_36__* pTable; scalar_t__ bUnordered; } ;
typedef  TYPE_14__ Index ;
typedef  TYPE_15__ ExprList ;
typedef  TYPE_16__ Expr ;
typedef  TYPE_17__ CollSeq ;
typedef  int Bitmask ;

/* Variables and functions */
 scalar_t__ ALWAYS (int) ; 
 int BMS ; 
 int /*<<< orphan*/  HasRowid (TYPE_36__*) ; 
 int IsUniqueIndex (TYPE_14__*) ; 
 int MASKBIT (int) ; 
 scalar_t__ OptimizationDisabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQLITE_OrderByIdxJoin ; 
 scalar_t__ TK_COLUMN ; 
 scalar_t__ TK_IS ; 
 int WHERE_DISTINCTBY ; 
 int WHERE_GROUPBY ; 
 int WHERE_IPK ; 
 int WHERE_ONEROW ; 
 int WHERE_ORDERBY_LIMIT ; 
 int WHERE_VIRTUALTABLE ; 
 int WO_EQ ; 
 int WO_IN ; 
 int WO_IS ; 
 int WO_ISNULL ; 
 int XN_ROWID ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3ExprCollSeqMatch (TYPE_27__*,TYPE_16__*,TYPE_16__*) ; 
 scalar_t__ sqlite3ExprCompareSkip (TYPE_16__*,TYPE_16__*,int) ; 
 int /*<<< orphan*/  sqlite3ExprIsConstant (TYPE_16__*) ; 
 TYPE_17__* sqlite3ExprNNCollSeq (TYPE_27__*,TYPE_16__*) ; 
 TYPE_16__* sqlite3ExprSkipCollate (TYPE_16__*) ; 
 scalar_t__ sqlite3StrICmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3WhereExprUsage (int /*<<< orphan*/ *,TYPE_16__*) ; 
 TYPE_10__* sqlite3WhereFindTerm (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static i8 wherePathSatisfiesOrderBy(
  WhereInfo *pWInfo,    /* The WHERE clause */
  ExprList *pOrderBy,   /* ORDER BY or GROUP BY or DISTINCT clause to check */
  WherePath *pPath,     /* The WherePath to check */
  u16 wctrlFlags,       /* WHERE_GROUPBY or _DISTINCTBY or _ORDERBY_LIMIT */
  u16 nLoop,            /* Number of entries in pPath->aLoop[] */
  WhereLoop *pLast,     /* Add this WhereLoop to the end of pPath->aLoop[] */
  Bitmask *pRevMask     /* OUT: Mask of WhereLoops to run in reverse order */
){
  u8 revSet;            /* True if rev is known */
  u8 rev;               /* Composite sort order */
  u8 revIdx;            /* Index sort order */
  u8 isOrderDistinct;   /* All prior WhereLoops are order-distinct */
  u8 distinctColumns;   /* True if the loop has UNIQUE NOT NULL columns */
  u8 isMatch;           /* iColumn matches a term of the ORDER BY clause */
  u16 eqOpMask;         /* Allowed equality operators */
  u16 nKeyCol;          /* Number of key columns in pIndex */
  u16 nColumn;          /* Total number of ordered columns in the index */
  u16 nOrderBy;         /* Number terms in the ORDER BY clause */
  int iLoop;            /* Index of WhereLoop in pPath being processed */
  int i, j;             /* Loop counters */
  int iCur;             /* Cursor number for current WhereLoop */
  int iColumn;          /* A column number within table iCur */
  WhereLoop *pLoop = 0; /* Current WhereLoop being processed. */
  WhereTerm *pTerm;     /* A single term of the WHERE clause */
  Expr *pOBExpr;        /* An expression from the ORDER BY clause */
  CollSeq *pColl;       /* COLLATE function from an ORDER BY clause term */
  Index *pIndex;        /* The index associated with pLoop */
  sqlite3 *db = pWInfo->pParse->db;  /* Database connection */
  Bitmask obSat = 0;    /* Mask of ORDER BY terms satisfied so far */
  Bitmask obDone;       /* Mask of all ORDER BY terms */
  Bitmask orderDistinctMask;  /* Mask of all well-ordered loops */
  Bitmask ready;              /* Mask of inner loops */

  /*
  ** We say the WhereLoop is "one-row" if it generates no more than one
  ** row of output.  A WhereLoop is one-row if all of the following are true:
  **  (a) All index columns match with WHERE_COLUMN_EQ.
  **  (b) The index is unique
  ** Any WhereLoop with an WHERE_COLUMN_EQ constraint on the rowid is one-row.
  ** Every one-row WhereLoop will have the WHERE_ONEROW bit set in wsFlags.
  **
  ** We say the WhereLoop is "order-distinct" if the set of columns from
  ** that WhereLoop that are in the ORDER BY clause are different for every
  ** row of the WhereLoop.  Every one-row WhereLoop is automatically
  ** order-distinct.   A WhereLoop that has no columns in the ORDER BY clause
  ** is not order-distinct. To be order-distinct is not quite the same as being
  ** UNIQUE since a UNIQUE column or index can have multiple rows that 
  ** are NULL and NULL values are equivalent for the purpose of order-distinct.
  ** To be order-distinct, the columns must be UNIQUE and NOT NULL.
  **
  ** The rowid for a table is always UNIQUE and NOT NULL so whenever the
  ** rowid appears in the ORDER BY clause, the corresponding WhereLoop is
  ** automatically order-distinct.
  */

  assert( pOrderBy!=0 );
  if( nLoop && OptimizationDisabled(db, SQLITE_OrderByIdxJoin) ) return 0;

  nOrderBy = pOrderBy->nExpr;
  testcase( nOrderBy==BMS-1 );
  if( nOrderBy>BMS-1 ) return 0;  /* Cannot optimize overly large ORDER BYs */
  isOrderDistinct = 1;
  obDone = MASKBIT(nOrderBy)-1;
  orderDistinctMask = 0;
  ready = 0;
  eqOpMask = WO_EQ | WO_IS | WO_ISNULL;
  if( wctrlFlags & WHERE_ORDERBY_LIMIT ) eqOpMask |= WO_IN;
  for(iLoop=0; isOrderDistinct && obSat<obDone && iLoop<=nLoop; iLoop++){
    if( iLoop>0 ) ready |= pLoop->maskSelf;
    if( iLoop<nLoop ){
      pLoop = pPath->aLoop[iLoop];
      if( wctrlFlags & WHERE_ORDERBY_LIMIT ) continue;
    }else{
      pLoop = pLast;
    }
    if( pLoop->wsFlags & WHERE_VIRTUALTABLE ){
      if( pLoop->u.vtab.isOrdered ) obSat = obDone;
      break;
    }else{
      pLoop->u.btree.nIdxCol = 0;
    }
    iCur = pWInfo->pTabList->a[pLoop->iTab].iCursor;

    /* Mark off any ORDER BY term X that is a column in the table of
    ** the current loop for which there is term in the WHERE
    ** clause of the form X IS NULL or X=? that reference only outer
    ** loops.
    */
    for(i=0; i<nOrderBy; i++){
      if( MASKBIT(i) & obSat ) continue;
      pOBExpr = sqlite3ExprSkipCollate(pOrderBy->a[i].pExpr);
      if( pOBExpr->op!=TK_COLUMN ) continue;
      if( pOBExpr->iTable!=iCur ) continue;
      pTerm = sqlite3WhereFindTerm(&pWInfo->sWC, iCur, pOBExpr->iColumn,
                       ~ready, eqOpMask, 0);
      if( pTerm==0 ) continue;
      if( pTerm->eOperator==WO_IN ){
        /* IN terms are only valid for sorting in the ORDER BY LIMIT 
        ** optimization, and then only if they are actually used
        ** by the query plan */
        assert( wctrlFlags & WHERE_ORDERBY_LIMIT );
        for(j=0; j<pLoop->nLTerm && pTerm!=pLoop->aLTerm[j]; j++){}
        if( j>=pLoop->nLTerm ) continue;
      }
      if( (pTerm->eOperator&(WO_EQ|WO_IS))!=0 && pOBExpr->iColumn>=0 ){
        if( sqlite3ExprCollSeqMatch(pWInfo->pParse, 
                  pOrderBy->a[i].pExpr, pTerm->pExpr)==0 ){
          continue;
        }
        testcase( pTerm->pExpr->op==TK_IS );
      }
      obSat |= MASKBIT(i);
    }

    if( (pLoop->wsFlags & WHERE_ONEROW)==0 ){
      if( pLoop->wsFlags & WHERE_IPK ){
        pIndex = 0;
        nKeyCol = 0;
        nColumn = 1;
      }else if( (pIndex = pLoop->u.btree.pIndex)==0 || pIndex->bUnordered ){
        return 0;
      }else{
        nKeyCol = pIndex->nKeyCol;
        nColumn = pIndex->nColumn;
        assert( nColumn==nKeyCol+1 || !HasRowid(pIndex->pTable) );
        assert( pIndex->aiColumn[nColumn-1]==XN_ROWID
                          || !HasRowid(pIndex->pTable));
        isOrderDistinct = IsUniqueIndex(pIndex);
      }

      /* Loop through all columns of the index and deal with the ones
      ** that are not constrained by == or IN.
      */
      rev = revSet = 0;
      distinctColumns = 0;
      for(j=0; j<nColumn; j++){
        u8 bOnce = 1; /* True to run the ORDER BY search loop */

        assert( j>=pLoop->u.btree.nEq 
            || (pLoop->aLTerm[j]==0)==(j<pLoop->nSkip)
        );
        if( j<pLoop->u.btree.nEq && j>=pLoop->nSkip ){
          u16 eOp = pLoop->aLTerm[j]->eOperator;

          /* Skip over == and IS and ISNULL terms.  (Also skip IN terms when
          ** doing WHERE_ORDERBY_LIMIT processing). 
          **
          ** If the current term is a column of an ((?,?) IN (SELECT...)) 
          ** expression for which the SELECT returns more than one column,
          ** check that it is the only column used by this loop. Otherwise,
          ** if it is one of two or more, none of the columns can be
          ** considered to match an ORDER BY term.  */
          if( (eOp & eqOpMask)!=0 ){
            if( eOp & WO_ISNULL ){
              testcase( isOrderDistinct );
              isOrderDistinct = 0;
            }
            continue;  
          }else if( ALWAYS(eOp & WO_IN) ){
            /* ALWAYS() justification: eOp is an equality operator due to the
            ** j<pLoop->u.btree.nEq constraint above.  Any equality other
            ** than WO_IN is captured by the previous "if".  So this one
            ** always has to be WO_IN. */
            Expr *pX = pLoop->aLTerm[j]->pExpr;
            for(i=j+1; i<pLoop->u.btree.nEq; i++){
              if( pLoop->aLTerm[i]->pExpr==pX ){
                assert( (pLoop->aLTerm[i]->eOperator & WO_IN) );
                bOnce = 0;
                break;
              }
            }
          }
        }

        /* Get the column number in the table (iColumn) and sort order
        ** (revIdx) for the j-th column of the index.
        */
        if( pIndex ){
          iColumn = pIndex->aiColumn[j];
          revIdx = pIndex->aSortOrder[j];
          if( iColumn==pIndex->pTable->iPKey ) iColumn = XN_ROWID;
        }else{
          iColumn = XN_ROWID;
          revIdx = 0;
        }

        /* An unconstrained column that might be NULL means that this
        ** WhereLoop is not well-ordered
        */
        if( isOrderDistinct
         && iColumn>=0
         && j>=pLoop->u.btree.nEq
         && pIndex->pTable->aCol[iColumn].notNull==0
        ){
          isOrderDistinct = 0;
        }

        /* Find the ORDER BY term that corresponds to the j-th column
        ** of the index and mark that ORDER BY term off 
        */
        isMatch = 0;
        for(i=0; bOnce && i<nOrderBy; i++){
          if( MASKBIT(i) & obSat ) continue;
          pOBExpr = sqlite3ExprSkipCollate(pOrderBy->a[i].pExpr);
          testcase( wctrlFlags & WHERE_GROUPBY );
          testcase( wctrlFlags & WHERE_DISTINCTBY );
          if( (wctrlFlags & (WHERE_GROUPBY|WHERE_DISTINCTBY))==0 ) bOnce = 0;
          if( iColumn>=XN_ROWID ){
            if( pOBExpr->op!=TK_COLUMN ) continue;
            if( pOBExpr->iTable!=iCur ) continue;
            if( pOBExpr->iColumn!=iColumn ) continue;
          }else{
            Expr *pIdxExpr = pIndex->aColExpr->a[j].pExpr;
            if( sqlite3ExprCompareSkip(pOBExpr, pIdxExpr, iCur) ){
              continue;
            }
          }
          if( iColumn!=XN_ROWID ){
            pColl = sqlite3ExprNNCollSeq(pWInfo->pParse, pOrderBy->a[i].pExpr);
            if( sqlite3StrICmp(pColl->zName, pIndex->azColl[j])!=0 ) continue;
          }
          pLoop->u.btree.nIdxCol = j+1;
          isMatch = 1;
          break;
        }
        if( isMatch && (wctrlFlags & WHERE_GROUPBY)==0 ){
          /* Make sure the sort order is compatible in an ORDER BY clause.
          ** Sort order is irrelevant for a GROUP BY clause. */
          if( revSet ){
            if( (rev ^ revIdx)!=pOrderBy->a[i].sortOrder ) isMatch = 0;
          }else{
            rev = revIdx ^ pOrderBy->a[i].sortOrder;
            if( rev ) *pRevMask |= MASKBIT(iLoop);
            revSet = 1;
          }
        }
        if( isMatch ){
          if( iColumn==XN_ROWID ){
            testcase( distinctColumns==0 );
            distinctColumns = 1;
          }
          obSat |= MASKBIT(i);
        }else{
          /* No match found */
          if( j==0 || j<nKeyCol ){
            testcase( isOrderDistinct!=0 );
            isOrderDistinct = 0;
          }
          break;
        }
      } /* end Loop over all index columns */
      if( distinctColumns ){
        testcase( isOrderDistinct==0 );
        isOrderDistinct = 1;
      }
    } /* end-if not one-row */

    /* Mark off any other ORDER BY terms that reference pLoop */
    if( isOrderDistinct ){
      orderDistinctMask |= pLoop->maskSelf;
      for(i=0; i<nOrderBy; i++){
        Expr *p;
        Bitmask mTerm;
        if( MASKBIT(i) & obSat ) continue;
        p = pOrderBy->a[i].pExpr;
        mTerm = sqlite3WhereExprUsage(&pWInfo->sMaskSet,p);
        if( mTerm==0 && !sqlite3ExprIsConstant(p) ) continue;
        if( (mTerm&~orderDistinctMask)==0 ){
          obSat |= MASKBIT(i);
        }
      }
    }
  } /* End the loop over all WhereLoops from outer-most down to inner-most */
  if( obSat==obDone ) return (i8)nOrderBy;
  if( !isOrderDistinct ){
    for(i=nOrderBy-1; i>0; i--){
      Bitmask m = MASKBIT(i) - 1;
      if( (obSat&m)==m ) return i;
    }
    return 0;
  }
  return -1;
}