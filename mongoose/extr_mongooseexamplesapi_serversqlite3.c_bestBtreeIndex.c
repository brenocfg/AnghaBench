#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_52__   TYPE_9__ ;
typedef  struct TYPE_51__   TYPE_8__ ;
typedef  struct TYPE_50__   TYPE_7__ ;
typedef  struct TYPE_49__   TYPE_6__ ;
typedef  struct TYPE_48__   TYPE_5__ ;
typedef  struct TYPE_47__   TYPE_4__ ;
typedef  struct TYPE_46__   TYPE_3__ ;
typedef  struct TYPE_45__   TYPE_35__ ;
typedef  struct TYPE_44__   TYPE_2__ ;
typedef  struct TYPE_43__   TYPE_20__ ;
typedef  struct TYPE_42__   TYPE_1__ ;
typedef  struct TYPE_41__   TYPE_15__ ;
typedef  struct TYPE_40__   TYPE_13__ ;
typedef  struct TYPE_39__   TYPE_12__ ;
typedef  struct TYPE_38__   TYPE_11__ ;
typedef  struct TYPE_37__   TYPE_10__ ;

/* Type definitions */
typedef  int tRowcnt ;
struct SrcList_item {int iCursor; int jointype; scalar_t__ notIndexed; int colUsed; TYPE_10__* pIndex; TYPE_1__* pTab; } ;
typedef  int /*<<< orphan*/  pc ;
struct TYPE_52__ {int eOperator; int wtFlags; int prereqAll; TYPE_11__* pWC; int /*<<< orphan*/  prereqRight; TYPE_15__* pExpr; } ;
typedef  TYPE_9__ WhereTerm ;
struct TYPE_50__ {TYPE_10__* pIdx; } ;
struct TYPE_51__ {int nOBSat; int nEq; int wsFlags; double nRow; TYPE_7__ u; } ;
struct TYPE_37__ {int rCost; int nColumn; int* aiColumn; int* aiRowEst; scalar_t__ onError; char* zName; scalar_t__ bUnordered; TYPE_8__ plan; int /*<<< orphan*/  used; struct TYPE_37__* pNext; TYPE_1__* pTable; } ;
typedef  TYPE_10__ WhereCost ;
struct TYPE_38__ {int wctrlFlags; int nTerm; TYPE_9__* a; int /*<<< orphan*/  pMaskSet; } ;
typedef  TYPE_11__ WhereClause ;
struct TYPE_39__ {int i; scalar_t__ pDistinct; int notValid; TYPE_10__ cost; TYPE_6__* pOrderBy; int /*<<< orphan*/  notReady; TYPE_5__* aLevel; struct SrcList_item* pSrc; TYPE_11__* pWC; TYPE_13__* pParse; } ;
typedef  TYPE_12__ WhereBestIdx ;
struct TYPE_49__ {int nExpr; } ;
struct TYPE_47__ {int nOBSat; int wsFlags; } ;
struct TYPE_48__ {TYPE_4__ plan; } ;
struct TYPE_46__ {TYPE_2__* pList; } ;
struct TYPE_45__ {int flags; } ;
struct TYPE_44__ {int nExpr; } ;
struct TYPE_43__ {scalar_t__ bUseCis; } ;
struct TYPE_42__ {int nRowEst; int /*<<< orphan*/  zName; TYPE_10__* pIndex; } ;
struct TYPE_41__ {TYPE_3__ x; } ;
struct TYPE_40__ {TYPE_35__* db; } ;
typedef  TYPE_13__ Parse ;
typedef  TYPE_10__ Index ;
typedef  TYPE_15__ Expr ;
typedef  int Bitmask ;

/* Variables and functions */
 scalar_t__ ALWAYS (int /*<<< orphan*/ ) ; 
 int BMS ; 
 int /*<<< orphan*/  EP_xIsSelect ; 
 scalar_t__ ExprHasProperty (TYPE_15__*,int /*<<< orphan*/ ) ; 
 int JT_LEFT ; 
 scalar_t__ OE_None ; 
 scalar_t__ OE_Replace ; 
 scalar_t__ OptimizationEnabled (TYPE_35__*,int /*<<< orphan*/ ) ; 
 int SQLITE_BIG_DBL ; 
 int /*<<< orphan*/  SQLITE_CoverIdxScan ; 
 int SQLITE_ReverseOrder ; 
 int TERM_VIRTUAL ; 
 int /*<<< orphan*/  WHERETRACE (char*) ; 
 int WHERE_ALL_UNIQUE ; 
 int WHERE_BTM_LIMIT ; 
 int WHERE_COLUMN_EQ ; 
 int WHERE_COLUMN_IN ; 
 int WHERE_COLUMN_NULL ; 
 int WHERE_COLUMN_RANGE ; 
 int WHERE_COVER_SCAN ; 
 int WHERE_DISTINCT ; 
 int WHERE_IDX_ONLY ; 
 int WHERE_NOT_FULLSCAN ; 
 int WHERE_OB_UNIQUE ; 
 int WHERE_ONEPASS_DESIRED ; 
 int WHERE_ORDERED ; 
 int WHERE_REVERSE ; 
 int WHERE_ROWID_EQ ; 
 int WHERE_ROWID_RANGE ; 
 int WHERE_TOP_LIMIT ; 
 int WHERE_UNIQUE ; 
 int WO_EQ ; 
 int WO_GE ; 
 int WO_GT ; 
 int WO_IN ; 
 int WO_ISNULL ; 
 int WO_LE ; 
 int WO_LT ; 
 int WO_NOOP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bestAutomaticIndex (TYPE_12__*) ; 
 int /*<<< orphan*/  bestOrClauseIndex (TYPE_12__*) ; 
 scalar_t__ compareCost (TYPE_10__*,TYPE_10__*) ; 
 int estLog (int const) ; 
 TYPE_9__* findTerm (TYPE_11__*,int,int,int /*<<< orphan*/ ,int,TYPE_10__*) ; 
 int getMask (int /*<<< orphan*/ ,int) ; 
 scalar_t__ isDistinctIndex (TYPE_13__*,TYPE_11__*,TYPE_10__*,int,scalar_t__,size_t) ; 
 int isSortingIndex (TYPE_12__*,TYPE_10__*,int,int*,int*) ; 
 int /*<<< orphan*/  memset (TYPE_10__*,int /*<<< orphan*/ ,int) ; 
 TYPE_20__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  testcase (int) ; 
 int /*<<< orphan*/  whereRangeScanEst (TYPE_13__*,TYPE_10__*,size_t,TYPE_9__*,TYPE_9__*,double*) ; 

__attribute__((used)) static void bestBtreeIndex(WhereBestIdx *p){
  Parse *pParse = p->pParse;  /* The parsing context */
  WhereClause *pWC = p->pWC;  /* The WHERE clause */
  struct SrcList_item *pSrc = p->pSrc; /* The FROM clause term to search */
  int iCur = pSrc->iCursor;   /* The cursor of the table to be accessed */
  Index *pProbe;              /* An index we are evaluating */
  Index *pIdx;                /* Copy of pProbe, or zero for IPK index */
  int eqTermMask;             /* Current mask of valid equality operators */
  int idxEqTermMask;          /* Index mask of valid equality operators */
  Index sPk;                  /* A fake index object for the primary key */
  tRowcnt aiRowEstPk[2];      /* The aiRowEst[] value for the sPk index */
  int aiColumnPk = -1;        /* The aColumn[] value for the sPk index */
  int wsFlagMask;             /* Allowed flags in p->cost.plan.wsFlag */
  int nPriorSat;              /* ORDER BY terms satisfied by outer loops */
  int nOrderBy;               /* Number of ORDER BY terms */
  char bSortInit;             /* Initializer for bSort in inner loop */
  char bDistInit;             /* Initializer for bDist in inner loop */


  /* Initialize the cost to a worst-case value */
  memset(&p->cost, 0, sizeof(p->cost));
  p->cost.rCost = SQLITE_BIG_DBL;

  /* If the pSrc table is the right table of a LEFT JOIN then we may not
  ** use an index to satisfy IS NULL constraints on that table.  This is
  ** because columns might end up being NULL if the table does not match -
  ** a circumstance which the index cannot help us discover.  Ticket #2177.
  */
  if( pSrc->jointype & JT_LEFT ){
    idxEqTermMask = WO_EQ|WO_IN;
  }else{
    idxEqTermMask = WO_EQ|WO_IN|WO_ISNULL;
  }

  if( pSrc->pIndex ){
    /* An INDEXED BY clause specifies a particular index to use */
    pIdx = pProbe = pSrc->pIndex;
    wsFlagMask = ~(WHERE_ROWID_EQ|WHERE_ROWID_RANGE);
    eqTermMask = idxEqTermMask;
  }else{
    /* There is no INDEXED BY clause.  Create a fake Index object in local
    ** variable sPk to represent the rowid primary key index.  Make this
    ** fake index the first in a chain of Index objects with all of the real
    ** indices to follow */
    Index *pFirst;                  /* First of real indices on the table */
    memset(&sPk, 0, sizeof(Index));
    sPk.nColumn = 1;
    sPk.aiColumn = &aiColumnPk;
    sPk.aiRowEst = aiRowEstPk;
    sPk.onError = OE_Replace;
    sPk.pTable = pSrc->pTab;
    aiRowEstPk[0] = pSrc->pTab->nRowEst;
    aiRowEstPk[1] = 1;
    pFirst = pSrc->pTab->pIndex;
    if( pSrc->notIndexed==0 ){
      /* The real indices of the table are only considered if the
      ** NOT INDEXED qualifier is omitted from the FROM clause */
      sPk.pNext = pFirst;
    }
    pProbe = &sPk;
    wsFlagMask = ~(
        WHERE_COLUMN_IN|WHERE_COLUMN_EQ|WHERE_COLUMN_NULL|WHERE_COLUMN_RANGE
    );
    eqTermMask = WO_EQ|WO_IN;
    pIdx = 0;
  }

  nOrderBy = p->pOrderBy ? p->pOrderBy->nExpr : 0;
  if( p->i ){
    nPriorSat = p->aLevel[p->i-1].plan.nOBSat;
    bSortInit = nPriorSat<nOrderBy;
    bDistInit = 0;
  }else{
    nPriorSat = 0;
    bSortInit = nOrderBy>0;
    bDistInit = p->pDistinct!=0;
  }

  /* Loop over all indices looking for the best one to use
  */
  for(; pProbe; pIdx=pProbe=pProbe->pNext){
    const tRowcnt * const aiRowEst = pProbe->aiRowEst;
    WhereCost pc;               /* Cost of using pProbe */
    double log10N = (double)1;  /* base-10 logarithm of nRow (inexact) */

    /* The following variables are populated based on the properties of
    ** index being evaluated. They are then used to determine the expected
    ** cost and number of rows returned.
    **
    **  pc.plan.nEq: 
    **    Number of equality terms that can be implemented using the index.
    **    In other words, the number of initial fields in the index that
    **    are used in == or IN or NOT NULL constraints of the WHERE clause.
    **
    **  nInMul:  
    **    The "in-multiplier". This is an estimate of how many seek operations 
    **    SQLite must perform on the index in question. For example, if the 
    **    WHERE clause is:
    **
    **      WHERE a IN (1, 2, 3) AND b IN (4, 5, 6)
    **
    **    SQLite must perform 9 lookups on an index on (a, b), so nInMul is 
    **    set to 9. Given the same schema and either of the following WHERE 
    **    clauses:
    **
    **      WHERE a =  1
    **      WHERE a >= 2
    **
    **    nInMul is set to 1.
    **
    **    If there exists a WHERE term of the form "x IN (SELECT ...)", then 
    **    the sub-select is assumed to return 25 rows for the purposes of 
    **    determining nInMul.
    **
    **  bInEst:  
    **    Set to true if there was at least one "x IN (SELECT ...)" term used 
    **    in determining the value of nInMul.  Note that the RHS of the
    **    IN operator must be a SELECT, not a value list, for this variable
    **    to be true.
    **
    **  rangeDiv:
    **    An estimate of a divisor by which to reduce the search space due
    **    to inequality constraints.  In the absence of sqlite_stat3 ANALYZE
    **    data, a single inequality reduces the search space to 1/4rd its
    **    original size (rangeDiv==4).  Two inequalities reduce the search
    **    space to 1/16th of its original size (rangeDiv==16).
    **
    **  bSort:   
    **    Boolean. True if there is an ORDER BY clause that will require an 
    **    external sort (i.e. scanning the index being evaluated will not 
    **    correctly order records).
    **
    **  bDist:
    **    Boolean. True if there is a DISTINCT clause that will require an 
    **    external btree.
    **
    **  bLookup: 
    **    Boolean. True if a table lookup is required for each index entry
    **    visited.  In other words, true if this is not a covering index.
    **    This is always false for the rowid primary key index of a table.
    **    For other indexes, it is true unless all the columns of the table
    **    used by the SELECT statement are present in the index (such an
    **    index is sometimes described as a covering index).
    **    For example, given the index on (a, b), the second of the following 
    **    two queries requires table b-tree lookups in order to find the value
    **    of column c, but the first does not because columns a and b are
    **    both available in the index.
    **
    **             SELECT a, b    FROM tbl WHERE a = 1;
    **             SELECT a, b, c FROM tbl WHERE a = 1;
    */
    int bInEst = 0;               /* True if "x IN (SELECT...)" seen */
    int nInMul = 1;               /* Number of distinct equalities to lookup */
    double rangeDiv = (double)1;  /* Estimated reduction in search space */
    int nBound = 0;               /* Number of range constraints seen */
    char bSort = bSortInit;       /* True if external sort required */
    char bDist = bDistInit;       /* True if index cannot help with DISTINCT */
    char bLookup = 0;             /* True if not a covering index */
    WhereTerm *pTerm;             /* A single term of the WHERE clause */
#ifdef SQLITE_ENABLE_STAT3
    WhereTerm *pFirstTerm = 0;    /* First term matching the index */
#endif

    WHERETRACE((
      "   %s(%s):\n",
      pSrc->pTab->zName, (pIdx ? pIdx->zName : "ipk")
    ));
    memset(&pc, 0, sizeof(pc));
    pc.plan.nOBSat = nPriorSat;

    /* Determine the values of pc.plan.nEq and nInMul */
    for(pc.plan.nEq=0; pc.plan.nEq<pProbe->nColumn; pc.plan.nEq++){
      int j = pProbe->aiColumn[pc.plan.nEq];
      pTerm = findTerm(pWC, iCur, j, p->notReady, eqTermMask, pIdx);
      if( pTerm==0 ) break;
      pc.plan.wsFlags |= (WHERE_COLUMN_EQ|WHERE_ROWID_EQ);
      testcase( pTerm->pWC!=pWC );
      if( pTerm->eOperator & WO_IN ){
        Expr *pExpr = pTerm->pExpr;
        pc.plan.wsFlags |= WHERE_COLUMN_IN;
        if( ExprHasProperty(pExpr, EP_xIsSelect) ){
          /* "x IN (SELECT ...)":  Assume the SELECT returns 25 rows */
          nInMul *= 25;
          bInEst = 1;
        }else if( ALWAYS(pExpr->x.pList && pExpr->x.pList->nExpr) ){
          /* "x IN (value, value, ...)" */
          nInMul *= pExpr->x.pList->nExpr;
        }
      }else if( pTerm->eOperator & WO_ISNULL ){
        pc.plan.wsFlags |= WHERE_COLUMN_NULL;
      }
#ifdef SQLITE_ENABLE_STAT3
      if( pc.plan.nEq==0 && pProbe->aSample ) pFirstTerm = pTerm;
#endif
      pc.used |= pTerm->prereqRight;
    }
 
    /* If the index being considered is UNIQUE, and there is an equality 
    ** constraint for all columns in the index, then this search will find
    ** at most a single row. In this case set the WHERE_UNIQUE flag to 
    ** indicate this to the caller.
    **
    ** Otherwise, if the search may find more than one row, test to see if
    ** there is a range constraint on indexed column (pc.plan.nEq+1) that
    ** can be optimized using the index. 
    */
    if( pc.plan.nEq==pProbe->nColumn && pProbe->onError!=OE_None ){
      testcase( pc.plan.wsFlags & WHERE_COLUMN_IN );
      testcase( pc.plan.wsFlags & WHERE_COLUMN_NULL );
      if( (pc.plan.wsFlags & (WHERE_COLUMN_IN|WHERE_COLUMN_NULL))==0 ){
        pc.plan.wsFlags |= WHERE_UNIQUE;
        if( p->i==0 || (p->aLevel[p->i-1].plan.wsFlags & WHERE_ALL_UNIQUE)!=0 ){
          pc.plan.wsFlags |= WHERE_ALL_UNIQUE;
        }
      }
    }else if( pProbe->bUnordered==0 ){
      int j;
      j = (pc.plan.nEq==pProbe->nColumn ? -1 : pProbe->aiColumn[pc.plan.nEq]);
      if( findTerm(pWC, iCur, j, p->notReady, WO_LT|WO_LE|WO_GT|WO_GE, pIdx) ){
        WhereTerm *pTop, *pBtm;
        pTop = findTerm(pWC, iCur, j, p->notReady, WO_LT|WO_LE, pIdx);
        pBtm = findTerm(pWC, iCur, j, p->notReady, WO_GT|WO_GE, pIdx);
        whereRangeScanEst(pParse, pProbe, pc.plan.nEq, pBtm, pTop, &rangeDiv);
        if( pTop ){
          nBound = 1;
          pc.plan.wsFlags |= WHERE_TOP_LIMIT;
          pc.used |= pTop->prereqRight;
          testcase( pTop->pWC!=pWC );
        }
        if( pBtm ){
          nBound++;
          pc.plan.wsFlags |= WHERE_BTM_LIMIT;
          pc.used |= pBtm->prereqRight;
          testcase( pBtm->pWC!=pWC );
        }
        pc.plan.wsFlags |= (WHERE_COLUMN_RANGE|WHERE_ROWID_RANGE);
      }
    }

    /* If there is an ORDER BY clause and the index being considered will
    ** naturally scan rows in the required order, set the appropriate flags
    ** in pc.plan.wsFlags. Otherwise, if there is an ORDER BY clause but
    ** the index will scan rows in a different order, set the bSort
    ** variable.  */
    if( bSort && (pSrc->jointype & JT_LEFT)==0 ){
      int bRev = 2;
      int bObUnique = 0;
      WHERETRACE(("      --> before isSortIndex: nPriorSat=%d\n",nPriorSat));
      pc.plan.nOBSat = isSortingIndex(p, pProbe, iCur, &bRev, &bObUnique);
      WHERETRACE(("      --> after  isSortIndex: bRev=%d bObU=%d nOBSat=%d\n",
                  bRev, bObUnique, pc.plan.nOBSat));
      if( nPriorSat<pc.plan.nOBSat || (pc.plan.wsFlags & WHERE_ALL_UNIQUE)!=0 ){
        pc.plan.wsFlags |= WHERE_ORDERED;
        if( bObUnique ) pc.plan.wsFlags |= WHERE_OB_UNIQUE;
      }
      if( nOrderBy==pc.plan.nOBSat ){
        bSort = 0;
        pc.plan.wsFlags |= WHERE_ROWID_RANGE|WHERE_COLUMN_RANGE;
      }
      if( bRev & 1 ) pc.plan.wsFlags |= WHERE_REVERSE;
    }

    /* If there is a DISTINCT qualifier and this index will scan rows in
    ** order of the DISTINCT expressions, clear bDist and set the appropriate
    ** flags in pc.plan.wsFlags. */
    if( bDist
     && isDistinctIndex(pParse, pWC, pProbe, iCur, p->pDistinct, pc.plan.nEq)
     && (pc.plan.wsFlags & WHERE_COLUMN_IN)==0
    ){
      bDist = 0;
      pc.plan.wsFlags |= WHERE_ROWID_RANGE|WHERE_COLUMN_RANGE|WHERE_DISTINCT;
    }

    /* If currently calculating the cost of using an index (not the IPK
    ** index), determine if all required column data may be obtained without 
    ** using the main table (i.e. if the index is a covering
    ** index for this query). If it is, set the WHERE_IDX_ONLY flag in
    ** pc.plan.wsFlags. Otherwise, set the bLookup variable to true.  */
    if( pIdx ){
      Bitmask m = pSrc->colUsed;
      int j;
      for(j=0; j<pIdx->nColumn; j++){
        int x = pIdx->aiColumn[j];
        if( x<BMS-1 ){
          m &= ~(((Bitmask)1)<<x);
        }
      }
      if( m==0 ){
        pc.plan.wsFlags |= WHERE_IDX_ONLY;
      }else{
        bLookup = 1;
      }
    }

    /*
    ** Estimate the number of rows of output.  For an "x IN (SELECT...)"
    ** constraint, do not let the estimate exceed half the rows in the table.
    */
    pc.plan.nRow = (double)(aiRowEst[pc.plan.nEq] * nInMul);
    if( bInEst && pc.plan.nRow*2>aiRowEst[0] ){
      pc.plan.nRow = aiRowEst[0]/2;
      nInMul = (int)(pc.plan.nRow / aiRowEst[pc.plan.nEq]);
    }

#ifdef SQLITE_ENABLE_STAT3
    /* If the constraint is of the form x=VALUE or x IN (E1,E2,...)
    ** and we do not think that values of x are unique and if histogram
    ** data is available for column x, then it might be possible
    ** to get a better estimate on the number of rows based on
    ** VALUE and how common that value is according to the histogram.
    */
    if( pc.plan.nRow>(double)1 && pc.plan.nEq==1
     && pFirstTerm!=0 && aiRowEst[1]>1 ){
      assert( (pFirstTerm->eOperator & (WO_EQ|WO_ISNULL|WO_IN))!=0 );
      if( pFirstTerm->eOperator & (WO_EQ|WO_ISNULL) ){
        testcase( pFirstTerm->eOperator & WO_EQ );
        testcase( pFirstTerm->eOperator & WO_EQUIV );
        testcase( pFirstTerm->eOperator & WO_ISNULL );
        whereEqualScanEst(pParse, pProbe, pFirstTerm->pExpr->pRight,
                          &pc.plan.nRow);
      }else if( bInEst==0 ){
        assert( pFirstTerm->eOperator & WO_IN );
        whereInScanEst(pParse, pProbe, pFirstTerm->pExpr->x.pList,
                       &pc.plan.nRow);
      }
    }
#endif /* SQLITE_ENABLE_STAT3 */

    /* Adjust the number of output rows and downward to reflect rows
    ** that are excluded by range constraints.
    */
    pc.plan.nRow = pc.plan.nRow/rangeDiv;
    if( pc.plan.nRow<1 ) pc.plan.nRow = 1;

    /* Experiments run on real SQLite databases show that the time needed
    ** to do a binary search to locate a row in a table or index is roughly
    ** log10(N) times the time to move from one row to the next row within
    ** a table or index.  The actual times can vary, with the size of
    ** records being an important factor.  Both moves and searches are
    ** slower with larger records, presumably because fewer records fit
    ** on one page and hence more pages have to be fetched.
    **
    ** The ANALYZE command and the sqlite_stat1 and sqlite_stat3 tables do
    ** not give us data on the relative sizes of table and index records.
    ** So this computation assumes table records are about twice as big
    ** as index records
    */
    if( (pc.plan.wsFlags&~(WHERE_REVERSE|WHERE_ORDERED|WHERE_OB_UNIQUE))
                                                              ==WHERE_IDX_ONLY
     && (pWC->wctrlFlags & WHERE_ONEPASS_DESIRED)==0
     && sqlite3GlobalConfig.bUseCis
     && OptimizationEnabled(pParse->db, SQLITE_CoverIdxScan)
    ){
      /* This index is not useful for indexing, but it is a covering index.
      ** A full-scan of the index might be a little faster than a full-scan
      ** of the table, so give this case a cost slightly less than a table
      ** scan. */
      pc.rCost = aiRowEst[0]*3 + pProbe->nColumn;
      pc.plan.wsFlags |= WHERE_COVER_SCAN|WHERE_COLUMN_RANGE;
    }else if( (pc.plan.wsFlags & WHERE_NOT_FULLSCAN)==0 ){
      /* The cost of a full table scan is a number of move operations equal
      ** to the number of rows in the table.
      **
      ** We add an additional 4x penalty to full table scans.  This causes
      ** the cost function to err on the side of choosing an index over
      ** choosing a full scan.  This 4x full-scan penalty is an arguable
      ** decision and one which we expect to revisit in the future.  But
      ** it seems to be working well enough at the moment.
      */
      pc.rCost = aiRowEst[0]*4;
      pc.plan.wsFlags &= ~WHERE_IDX_ONLY;
      if( pIdx ){
        pc.plan.wsFlags &= ~WHERE_ORDERED;
        pc.plan.nOBSat = nPriorSat;
      }
    }else{
      log10N = estLog(aiRowEst[0]);
      pc.rCost = pc.plan.nRow;
      if( pIdx ){
        if( bLookup ){
          /* For an index lookup followed by a table lookup:
          **    nInMul index searches to find the start of each index range
          **  + nRow steps through the index
          **  + nRow table searches to lookup the table entry using the rowid
          */
          pc.rCost += (nInMul + pc.plan.nRow)*log10N;
        }else{
          /* For a covering index:
          **     nInMul index searches to find the initial entry 
          **   + nRow steps through the index
          */
          pc.rCost += nInMul*log10N;
        }
      }else{
        /* For a rowid primary key lookup:
        **    nInMult table searches to find the initial entry for each range
        **  + nRow steps through the table
        */
        pc.rCost += nInMul*log10N;
      }
    }

    /* Add in the estimated cost of sorting the result.  Actual experimental
    ** measurements of sorting performance in SQLite show that sorting time
    ** adds C*N*log10(N) to the cost, where N is the number of rows to be 
    ** sorted and C is a factor between 1.95 and 4.3.  We will split the
    ** difference and select C of 3.0.
    */
    if( bSort ){
      double m = estLog(pc.plan.nRow*(nOrderBy - pc.plan.nOBSat)/nOrderBy);
      m *= (double)(pc.plan.nOBSat ? 2 : 3);
      pc.rCost += pc.plan.nRow*m;
    }
    if( bDist ){
      pc.rCost += pc.plan.nRow*estLog(pc.plan.nRow)*3;
    }

    /**** Cost of using this index has now been computed ****/

    /* If there are additional constraints on this table that cannot
    ** be used with the current index, but which might lower the number
    ** of output rows, adjust the nRow value accordingly.  This only 
    ** matters if the current index is the least costly, so do not bother
    ** with this step if we already know this index will not be chosen.
    ** Also, never reduce the output row count below 2 using this step.
    **
    ** It is critical that the notValid mask be used here instead of
    ** the notReady mask.  When computing an "optimal" index, the notReady
    ** mask will only have one bit set - the bit for the current table.
    ** The notValid mask, on the other hand, always has all bits set for
    ** tables that are not in outer loops.  If notReady is used here instead
    ** of notValid, then a optimal index that depends on inner joins loops
    ** might be selected even when there exists an optimal index that has
    ** no such dependency.
    */
    if( pc.plan.nRow>2 && pc.rCost<=p->cost.rCost ){
      int k;                       /* Loop counter */
      int nSkipEq = pc.plan.nEq;   /* Number of == constraints to skip */
      int nSkipRange = nBound;     /* Number of < constraints to skip */
      Bitmask thisTab;             /* Bitmap for pSrc */

      thisTab = getMask(pWC->pMaskSet, iCur);
      for(pTerm=pWC->a, k=pWC->nTerm; pc.plan.nRow>2 && k; k--, pTerm++){
        if( pTerm->wtFlags & TERM_VIRTUAL ) continue;
        if( (pTerm->prereqAll & p->notValid)!=thisTab ) continue;
        if( pTerm->eOperator & (WO_EQ|WO_IN|WO_ISNULL) ){
          if( nSkipEq ){
            /* Ignore the first pc.plan.nEq equality matches since the index
            ** has already accounted for these */
            nSkipEq--;
          }else{
            /* Assume each additional equality match reduces the result
            ** set size by a factor of 10 */
            pc.plan.nRow /= 10;
          }
        }else if( pTerm->eOperator & (WO_LT|WO_LE|WO_GT|WO_GE) ){
          if( nSkipRange ){
            /* Ignore the first nSkipRange range constraints since the index
            ** has already accounted for these */
            nSkipRange--;
          }else{
            /* Assume each additional range constraint reduces the result
            ** set size by a factor of 3.  Indexed range constraints reduce
            ** the search space by a larger factor: 4.  We make indexed range
            ** more selective intentionally because of the subjective 
            ** observation that indexed range constraints really are more
            ** selective in practice, on average. */
            pc.plan.nRow /= 3;
          }
        }else if( (pTerm->eOperator & WO_NOOP)==0 ){
          /* Any other expression lowers the output row count by half */
          pc.plan.nRow /= 2;
        }
      }
      if( pc.plan.nRow<2 ) pc.plan.nRow = 2;
    }


    WHERETRACE((
      "      nEq=%d nInMul=%d rangeDiv=%d bSort=%d bLookup=%d wsFlags=0x%08x\n"
      "      notReady=0x%llx log10N=%.1f nRow=%.1f cost=%.1f\n"
      "      used=0x%llx nOBSat=%d\n",
      pc.plan.nEq, nInMul, (int)rangeDiv, bSort, bLookup, pc.plan.wsFlags,
      p->notReady, log10N, pc.plan.nRow, pc.rCost, pc.used,
      pc.plan.nOBSat
    ));

    /* If this index is the best we have seen so far, then record this
    ** index and its cost in the p->cost structure.
    */
    if( (!pIdx || pc.plan.wsFlags) && compareCost(&pc, &p->cost) ){
      p->cost = pc;
      p->cost.plan.wsFlags &= wsFlagMask;
      p->cost.plan.u.pIdx = pIdx;
    }

    /* If there was an INDEXED BY clause, then only that one index is
    ** considered. */
    if( pSrc->pIndex ) break;

    /* Reset masks for the next index in the loop */
    wsFlagMask = ~(WHERE_ROWID_EQ|WHERE_ROWID_RANGE);
    eqTermMask = idxEqTermMask;
  }

  /* If there is no ORDER BY clause and the SQLITE_ReverseOrder flag
  ** is set, then reverse the order that the index will be scanned
  ** in. This is used for application testing, to help find cases
  ** where application behavior depends on the (undefined) order that
  ** SQLite outputs rows in in the absence of an ORDER BY clause.  */
  if( !p->pOrderBy && pParse->db->flags & SQLITE_ReverseOrder ){
    p->cost.plan.wsFlags |= WHERE_REVERSE;
  }

  assert( p->pOrderBy || (p->cost.plan.wsFlags&WHERE_ORDERED)==0 );
  assert( p->cost.plan.u.pIdx==0 || (p->cost.plan.wsFlags&WHERE_ROWID_EQ)==0 );
  assert( pSrc->pIndex==0 
       || p->cost.plan.u.pIdx==0 
       || p->cost.plan.u.pIdx==pSrc->pIndex 
  );

  WHERETRACE(("   best index is %s cost=%.1f\n",
         p->cost.plan.u.pIdx ? p->cost.plan.u.pIdx->zName : "ipk",
         p->cost.rCost));
  
  bestOrClauseIndex(p);
  bestAutomaticIndex(p);
  p->cost.plan.wsFlags |= eqTermMask;
}