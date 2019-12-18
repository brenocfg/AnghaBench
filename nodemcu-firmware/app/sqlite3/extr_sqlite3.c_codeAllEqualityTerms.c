#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_23__ {int wtFlags; int eOperator; TYPE_3__* pExpr; } ;
typedef  TYPE_4__ WhereTerm ;
struct TYPE_20__ {int nEq; TYPE_8__* pIndex; } ;
struct TYPE_21__ {TYPE_1__ btree; } ;
struct TYPE_24__ {int wsFlags; int nSkip; TYPE_4__** aLTerm; TYPE_2__ u; } ;
typedef  TYPE_5__ WhereLoop ;
struct TYPE_25__ {int iIdxCur; int addrBrk; int /*<<< orphan*/  addrSkip; TYPE_5__* pWLoop; } ;
typedef  TYPE_6__ WhereLevel ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_27__ {scalar_t__* aiColumn; int /*<<< orphan*/  zName; } ;
struct TYPE_26__ {int nMem; TYPE_10__* db; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_22__ {int flags; int /*<<< orphan*/ * pRight; } ;
struct TYPE_19__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_7__ Parse ;
typedef  TYPE_8__ Index ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int EP_xIsSelect ; 
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/  OP_Goto ; 
 int /*<<< orphan*/  OP_IsNull ; 
 int /*<<< orphan*/  OP_Last ; 
 int /*<<< orphan*/  OP_Rewind ; 
 int /*<<< orphan*/  OP_SCopy ; 
 int /*<<< orphan*/  OP_SeekGT ; 
 int /*<<< orphan*/  OP_SeekLT ; 
 char SQLITE_AFF_BLOB ; 
 int TERM_CODED ; 
 int TERM_IS ; 
 int TERM_VIRTUAL ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverageIf (int /*<<< orphan*/ *,int) ; 
 int WHERE_VIRTUALTABLE ; 
 int WO_IN ; 
 int WO_ISNULL ; 
 scalar_t__ XN_EXPR ; 
 int /*<<< orphan*/  assert (int) ; 
 int codeEqualityTerm (TYPE_7__*,TYPE_4__*,TYPE_6__*,int,int,int) ; 
 int /*<<< orphan*/  explainIndexColumnName (TYPE_8__*,int) ; 
 char sqlite3CompareAffinity (int /*<<< orphan*/ *,char) ; 
 char* sqlite3DbStrDup (TYPE_10__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3ExprCanBeNull (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3ExprNeedsNoAffinityChange (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  sqlite3IndexAffinityStr (TYPE_10__*,TYPE_8__*) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_7__*,int) ; 
 int sqlite3VdbeAddOp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4Int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int codeAllEqualityTerms(
  Parse *pParse,        /* Parsing context */
  WhereLevel *pLevel,   /* Which nested loop of the FROM we are coding */
  int bRev,             /* Reverse the order of IN operators */
  int nExtraReg,        /* Number of extra registers to allocate */
  char **pzAff          /* OUT: Set to point to affinity string */
){
  u16 nEq;                      /* The number of == or IN constraints to code */
  u16 nSkip;                    /* Number of left-most columns to skip */
  Vdbe *v = pParse->pVdbe;      /* The vm under construction */
  Index *pIdx;                  /* The index being used for this loop */
  WhereTerm *pTerm;             /* A single constraint term */
  WhereLoop *pLoop;             /* The WhereLoop object */
  int j;                        /* Loop counter */
  int regBase;                  /* Base register */
  int nReg;                     /* Number of registers to allocate */
  char *zAff;                   /* Affinity string to return */

  /* This module is only called on query plans that use an index. */
  pLoop = pLevel->pWLoop;
  assert( (pLoop->wsFlags & WHERE_VIRTUALTABLE)==0 );
  nEq = pLoop->u.btree.nEq;
  nSkip = pLoop->nSkip;
  pIdx = pLoop->u.btree.pIndex;
  assert( pIdx!=0 );

  /* Figure out how many memory cells we will need then allocate them.
  */
  regBase = pParse->nMem + 1;
  nReg = pLoop->u.btree.nEq + nExtraReg;
  pParse->nMem += nReg;

  zAff = sqlite3DbStrDup(pParse->db,sqlite3IndexAffinityStr(pParse->db,pIdx));
  assert( zAff!=0 || pParse->db->mallocFailed );

  if( nSkip ){
    int iIdxCur = pLevel->iIdxCur;
    sqlite3VdbeAddOp1(v, (bRev?OP_Last:OP_Rewind), iIdxCur);
    VdbeCoverageIf(v, bRev==0);
    VdbeCoverageIf(v, bRev!=0);
    VdbeComment((v, "begin skip-scan on %s", pIdx->zName));
    j = sqlite3VdbeAddOp0(v, OP_Goto);
    pLevel->addrSkip = sqlite3VdbeAddOp4Int(v, (bRev?OP_SeekLT:OP_SeekGT),
                            iIdxCur, 0, regBase, nSkip);
    VdbeCoverageIf(v, bRev==0);
    VdbeCoverageIf(v, bRev!=0);
    sqlite3VdbeJumpHere(v, j);
    for(j=0; j<nSkip; j++){
      sqlite3VdbeAddOp3(v, OP_Column, iIdxCur, j, regBase+j);
      testcase( pIdx->aiColumn[j]==XN_EXPR );
      VdbeComment((v, "%s", explainIndexColumnName(pIdx, j)));
    }
  }

  /* Evaluate the equality constraints
  */
  assert( zAff==0 || (int)strlen(zAff)>=nEq );
  for(j=nSkip; j<nEq; j++){
    int r1;
    pTerm = pLoop->aLTerm[j];
    assert( pTerm!=0 );
    /* The following testcase is true for indices with redundant columns.
    ** Ex: CREATE INDEX i1 ON t1(a,b,a); SELECT * FROM t1 WHERE a=0 AND b=0; */
    testcase( (pTerm->wtFlags & TERM_CODED)!=0 );
    testcase( pTerm->wtFlags & TERM_VIRTUAL );
    r1 = codeEqualityTerm(pParse, pTerm, pLevel, j, bRev, regBase+j);
    if( r1!=regBase+j ){
      if( nReg==1 ){
        sqlite3ReleaseTempReg(pParse, regBase);
        regBase = r1;
      }else{
        sqlite3VdbeAddOp2(v, OP_SCopy, r1, regBase+j);
      }
    }
    if( pTerm->eOperator & WO_IN ){
      if( pTerm->pExpr->flags & EP_xIsSelect ){
        /* No affinity ever needs to be (or should be) applied to a value
        ** from the RHS of an "? IN (SELECT ...)" expression. The
        ** sqlite3FindInIndex() routine has already ensured that the
        ** affinity of the comparison has been applied to the value.  */
        if( zAff ) zAff[j] = SQLITE_AFF_BLOB;
      }
    }else if( (pTerm->eOperator & WO_ISNULL)==0 ){
      Expr *pRight = pTerm->pExpr->pRight;
      if( (pTerm->wtFlags & TERM_IS)==0 && sqlite3ExprCanBeNull(pRight) ){
        sqlite3VdbeAddOp2(v, OP_IsNull, regBase+j, pLevel->addrBrk);
        VdbeCoverage(v);
      }
      if( zAff ){
        if( sqlite3CompareAffinity(pRight, zAff[j])==SQLITE_AFF_BLOB ){
          zAff[j] = SQLITE_AFF_BLOB;
        }
        if( sqlite3ExprNeedsNoAffinityChange(pRight, zAff[j]) ){
          zAff[j] = SQLITE_AFF_BLOB;
        }
      }
    }
  }
  *pzAff = zAff;
  return regBase;
}