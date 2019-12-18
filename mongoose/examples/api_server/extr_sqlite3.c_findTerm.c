#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_19__ {int leftColumn; } ;
struct TYPE_23__ {int leftCursor; int prereqRight; int eOperator; TYPE_9__* pExpr; TYPE_1__ u; } ;
typedef  TYPE_5__ WhereTerm ;
struct TYPE_24__ {int nTerm; TYPE_7__* pParse; TYPE_5__* a; struct TYPE_24__* pOuter; } ;
typedef  TYPE_6__ WhereClause ;
struct TYPE_27__ {int pLeft; scalar_t__ op; int iTable; int iColumn; int /*<<< orphan*/  pRight; } ;
struct TYPE_26__ {int* aiColumn; int nColumn; int /*<<< orphan*/ * azColl; TYPE_3__* pTable; } ;
struct TYPE_25__ {TYPE_4__* db; } ;
struct TYPE_22__ {TYPE_10__* pDfltColl; } ;
struct TYPE_21__ {TYPE_2__* aCol; } ;
struct TYPE_20__ {char affinity; } ;
struct TYPE_18__ {int /*<<< orphan*/  zName; } ;
typedef  TYPE_7__ Parse ;
typedef  TYPE_8__ Index ;
typedef  TYPE_9__ Expr ;
typedef  TYPE_10__ CollSeq ;
typedef  int Bitmask ;

/* Variables and functions */
 int ArraySize (int*) ; 
 scalar_t__ NEVER (int) ; 
 scalar_t__ TK_COLUMN ; 
 int WO_ALL ; 
 int WO_EQ ; 
 int WO_EQUIV ; 
 int WO_ISNULL ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_10__* sqlite3BinaryCompareCollSeq (TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 TYPE_9__* sqlite3ExprSkipCollate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3IndexAffinityOk (TYPE_9__*,char) ; 
 scalar_t__ sqlite3StrICmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WhereTerm *findTerm(
  WhereClause *pWC,     /* The WHERE clause to be searched */
  int iCur,             /* Cursor number of LHS */
  int iColumn,          /* Column number of LHS */
  Bitmask notReady,     /* RHS must not overlap with this mask */
  u32 op,               /* Mask of WO_xx values describing operator */
  Index *pIdx           /* Must be compatible with this index, if not NULL */
){
  WhereTerm *pTerm;            /* Term being examined as possible result */
  WhereTerm *pResult = 0;      /* The answer to return */
  WhereClause *pWCOrig = pWC;  /* Original pWC value */
  int j, k;                    /* Loop counters */
  Expr *pX;                /* Pointer to an expression */
  Parse *pParse;           /* Parsing context */
  int iOrigCol = iColumn;  /* Original value of iColumn */
  int nEquiv = 2;          /* Number of entires in aEquiv[] */
  int iEquiv = 2;          /* Number of entries of aEquiv[] processed so far */
  int aEquiv[22];          /* iCur,iColumn and up to 10 other equivalents */

  assert( iCur>=0 );
  aEquiv[0] = iCur;
  aEquiv[1] = iColumn;
  for(;;){
    for(pWC=pWCOrig; pWC; pWC=pWC->pOuter){
      for(pTerm=pWC->a, k=pWC->nTerm; k; k--, pTerm++){
        if( pTerm->leftCursor==iCur
          && pTerm->u.leftColumn==iColumn
        ){
          if( (pTerm->prereqRight & notReady)==0
           && (pTerm->eOperator & op & WO_ALL)!=0
          ){
            if( iOrigCol>=0 && pIdx && (pTerm->eOperator & WO_ISNULL)==0 ){
              CollSeq *pColl;
              char idxaff;
      
              pX = pTerm->pExpr;
              pParse = pWC->pParse;
              idxaff = pIdx->pTable->aCol[iOrigCol].affinity;
              if( !sqlite3IndexAffinityOk(pX, idxaff) ){
                continue;
              }
      
              /* Figure out the collation sequence required from an index for
              ** it to be useful for optimising expression pX. Store this
              ** value in variable pColl.
              */
              assert(pX->pLeft);
              pColl = sqlite3BinaryCompareCollSeq(pParse,pX->pLeft,pX->pRight);
              if( pColl==0 ) pColl = pParse->db->pDfltColl;
      
              for(j=0; pIdx->aiColumn[j]!=iOrigCol; j++){
                if( NEVER(j>=pIdx->nColumn) ) return 0;
              }
              if( sqlite3StrICmp(pColl->zName, pIdx->azColl[j]) ){
                continue;
              }
            }
            if( pTerm->prereqRight==0 && (pTerm->eOperator&WO_EQ)!=0 ){
              pResult = pTerm;
              goto findTerm_success;
            }else if( pResult==0 ){
              pResult = pTerm;
            }
          }
          if( (pTerm->eOperator & WO_EQUIV)!=0
           && nEquiv<ArraySize(aEquiv)
          ){
            pX = sqlite3ExprSkipCollate(pTerm->pExpr->pRight);
            assert( pX->op==TK_COLUMN );
            for(j=0; j<nEquiv; j+=2){
              if( aEquiv[j]==pX->iTable && aEquiv[j+1]==pX->iColumn ) break;
            }
            if( j==nEquiv ){
              aEquiv[j] = pX->iTable;
              aEquiv[j+1] = pX->iColumn;
              nEquiv += 2;
            }
          }
        }
      }
    }
    if( iEquiv>=nEquiv ) break;
    iCur = aEquiv[iEquiv++];
    iColumn = aEquiv[iEquiv++];
  }
findTerm_success:
  return pResult;
}