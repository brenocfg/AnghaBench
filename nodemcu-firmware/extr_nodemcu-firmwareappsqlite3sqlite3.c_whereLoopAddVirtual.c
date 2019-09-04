#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct SrcList_item {int /*<<< orphan*/  pTab; } ;
typedef  int /*<<< orphan*/  sqlite3_uint64 ;
struct TYPE_28__ {int nConstraint; int /*<<< orphan*/  idxStr; scalar_t__ needToFreeIdxStr; TYPE_5__* aConstraint; } ;
typedef  TYPE_6__ sqlite3_index_info ;
struct TYPE_29__ {int /*<<< orphan*/  pOrderBy; TYPE_8__* pNew; TYPE_10__* pWC; TYPE_9__* pWInfo; } ;
typedef  TYPE_7__ WhereLoopBuilder ;
struct TYPE_24__ {scalar_t__ needFree; } ;
struct TYPE_25__ {TYPE_2__ vtab; } ;
struct TYPE_30__ {size_t iTab; scalar_t__ prereq; TYPE_3__ u; scalar_t__ nLTerm; int /*<<< orphan*/  wsFlags; scalar_t__ rSetup; } ;
typedef  TYPE_8__ WhereLoop ;
struct TYPE_31__ {TYPE_1__* pTabList; TYPE_11__* pParse; } ;
typedef  TYPE_9__ WhereInfo ;
struct TYPE_21__ {TYPE_4__* a; } ;
typedef  TYPE_10__ WhereClause ;
struct TYPE_27__ {size_t iTermOffset; } ;
struct TYPE_26__ {scalar_t__ prereqRight; } ;
struct TYPE_23__ {struct SrcList_item* a; } ;
struct TYPE_22__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_11__ Parse ;
typedef  scalar_t__ Bitmask ;

/* Variables and functions */
 scalar_t__ ALLBITS ; 
 int IsVirtual (int /*<<< orphan*/ ) ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  WHERETRACE (int,char*) ; 
 int /*<<< orphan*/  WHERE_VIRTUALTABLE ; 
 int /*<<< orphan*/  WO_IN ; 
 TYPE_6__* allocateIndexInfo (TYPE_11__*,TYPE_10__*,scalar_t__,struct SrcList_item*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3DbFreeNN (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 
 int whereLoopAddVirtualOne (TYPE_7__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ whereLoopResize (int /*<<< orphan*/ ,TYPE_8__*,int) ; 

__attribute__((used)) static int whereLoopAddVirtual(
  WhereLoopBuilder *pBuilder,  /* WHERE clause information */
  Bitmask mPrereq,             /* Tables that must be scanned before this one */
  Bitmask mUnusable            /* Tables that must be scanned after this one */
){
  int rc = SQLITE_OK;          /* Return code */
  WhereInfo *pWInfo;           /* WHERE analysis context */
  Parse *pParse;               /* The parsing context */
  WhereClause *pWC;            /* The WHERE clause */
  struct SrcList_item *pSrc;   /* The FROM clause term to search */
  sqlite3_index_info *p;       /* Object to pass to xBestIndex() */
  int nConstraint;             /* Number of constraints in p */
  int bIn;                     /* True if plan uses IN(...) operator */
  WhereLoop *pNew;
  Bitmask mBest;               /* Tables used by best possible plan */
  u16 mNoOmit;

  assert( (mPrereq & mUnusable)==0 );
  pWInfo = pBuilder->pWInfo;
  pParse = pWInfo->pParse;
  pWC = pBuilder->pWC;
  pNew = pBuilder->pNew;
  pSrc = &pWInfo->pTabList->a[pNew->iTab];
  assert( IsVirtual(pSrc->pTab) );
  p = allocateIndexInfo(pParse, pWC, mUnusable, pSrc, pBuilder->pOrderBy,
      &mNoOmit);
  if( p==0 ) return SQLITE_NOMEM_BKPT;
  pNew->rSetup = 0;
  pNew->wsFlags = WHERE_VIRTUALTABLE;
  pNew->nLTerm = 0;
  pNew->u.vtab.needFree = 0;
  nConstraint = p->nConstraint;
  if( whereLoopResize(pParse->db, pNew, nConstraint) ){
    sqlite3DbFree(pParse->db, p);
    return SQLITE_NOMEM_BKPT;
  }

  /* First call xBestIndex() with all constraints usable. */
  WHERETRACE(0x40, ("  VirtualOne: all usable\n"));
  rc = whereLoopAddVirtualOne(pBuilder, mPrereq, ALLBITS, 0, p, mNoOmit, &bIn);

  /* If the call to xBestIndex() with all terms enabled produced a plan
  ** that does not require any source tables (IOW: a plan with mBest==0),
  ** then there is no point in making any further calls to xBestIndex()
  ** since they will all return the same result (if the xBestIndex()
  ** implementation is sane). */
  if( rc==SQLITE_OK && (mBest = (pNew->prereq & ~mPrereq))!=0 ){
    int seenZero = 0;             /* True if a plan with no prereqs seen */
    int seenZeroNoIN = 0;         /* Plan with no prereqs and no IN(...) seen */
    Bitmask mPrev = 0;
    Bitmask mBestNoIn = 0;

    /* If the plan produced by the earlier call uses an IN(...) term, call
    ** xBestIndex again, this time with IN(...) terms disabled. */
    if( bIn ){
      WHERETRACE(0x40, ("  VirtualOne: all usable w/o IN\n"));
      rc = whereLoopAddVirtualOne(
          pBuilder, mPrereq, ALLBITS, WO_IN, p, mNoOmit, &bIn);
      assert( bIn==0 );
      mBestNoIn = pNew->prereq & ~mPrereq;
      if( mBestNoIn==0 ){
        seenZero = 1;
        seenZeroNoIN = 1;
      }
    }

    /* Call xBestIndex once for each distinct value of (prereqRight & ~mPrereq)
    ** in the set of terms that apply to the current virtual table.  */
    while( rc==SQLITE_OK ){
      int i;
      Bitmask mNext = ALLBITS;
      assert( mNext>0 );
      for(i=0; i<nConstraint; i++){
        Bitmask mThis = (
            pWC->a[p->aConstraint[i].iTermOffset].prereqRight & ~mPrereq
        );
        if( mThis>mPrev && mThis<mNext ) mNext = mThis;
      }
      mPrev = mNext;
      if( mNext==ALLBITS ) break;
      if( mNext==mBest || mNext==mBestNoIn ) continue;
      WHERETRACE(0x40, ("  VirtualOne: mPrev=%04llx mNext=%04llx\n",
                       (sqlite3_uint64)mPrev, (sqlite3_uint64)mNext));
      rc = whereLoopAddVirtualOne(
          pBuilder, mPrereq, mNext|mPrereq, 0, p, mNoOmit, &bIn);
      if( pNew->prereq==mPrereq ){
        seenZero = 1;
        if( bIn==0 ) seenZeroNoIN = 1;
      }
    }

    /* If the calls to xBestIndex() in the above loop did not find a plan
    ** that requires no source tables at all (i.e. one guaranteed to be
    ** usable), make a call here with all source tables disabled */
    if( rc==SQLITE_OK && seenZero==0 ){
      WHERETRACE(0x40, ("  VirtualOne: all disabled\n"));
      rc = whereLoopAddVirtualOne(
          pBuilder, mPrereq, mPrereq, 0, p, mNoOmit, &bIn);
      if( bIn==0 ) seenZeroNoIN = 1;
    }

    /* If the calls to xBestIndex() have so far failed to find a plan
    ** that requires no source tables at all and does not use an IN(...)
    ** operator, make a final call to obtain one here.  */
    if( rc==SQLITE_OK && seenZeroNoIN==0 ){
      WHERETRACE(0x40, ("  VirtualOne: all disabled and w/o IN\n"));
      rc = whereLoopAddVirtualOne(
          pBuilder, mPrereq, mPrereq, WO_IN, p, mNoOmit, &bIn);
    }
  }

  if( p->needToFreeIdxStr ) sqlite3_free(p->idxStr);
  sqlite3DbFreeNN(pParse->db, p);
  return rc;
}