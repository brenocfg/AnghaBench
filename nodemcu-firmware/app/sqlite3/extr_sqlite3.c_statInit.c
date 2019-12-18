#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ tRowcnt ;
struct Stat4Sample {int iCol; scalar_t__* anDLt; scalar_t__* anLt; scalar_t__* anEq; } ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {scalar_t__* anLt; scalar_t__* anEq; scalar_t__* anDLt; } ;
struct TYPE_6__ {int nCol; int nKeyCol; int iGet; int mxSample; int iPrn; struct Stat4Sample* aBest; struct Stat4Sample* a; TYPE_1__ current; scalar_t__ nPSample; scalar_t__ nRow; int /*<<< orphan*/ * db; } ;
typedef  int /*<<< orphan*/  Stat4Sample ;
typedef  TYPE_2__ Stat4Accum ;

/* Variables and functions */
 int SQLITE_STAT4_SAMPLES ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* sqlite3DbMallocZero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 
 int sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat4Destructor ; 

__attribute__((used)) static void statInit(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  Stat4Accum *p;
  int nCol;                       /* Number of columns in index being sampled */
  int nKeyCol;                    /* Number of key columns */
  int nColUp;                     /* nCol rounded up for alignment */
  int n;                          /* Bytes of space to allocate */
  sqlite3 *db;                    /* Database connection */
#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
  int mxSample = SQLITE_STAT4_SAMPLES;
#endif

  /* Decode the three function arguments */
  UNUSED_PARAMETER(argc);
  nCol = sqlite3_value_int(argv[0]);
  assert( nCol>0 );
  nColUp = sizeof(tRowcnt)<8 ? (nCol+1)&~1 : nCol;
  nKeyCol = sqlite3_value_int(argv[1]);
  assert( nKeyCol<=nCol );
  assert( nKeyCol>0 );

  /* Allocate the space required for the Stat4Accum object */
  n = sizeof(*p)
    + sizeof(tRowcnt)*nColUp                  /* Stat4Accum.anEq */
    + sizeof(tRowcnt)*nColUp                  /* Stat4Accum.anDLt */
#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
    + sizeof(tRowcnt)*nColUp                  /* Stat4Accum.anLt */
    + sizeof(Stat4Sample)*(nCol+mxSample)     /* Stat4Accum.aBest[], a[] */
    + sizeof(tRowcnt)*3*nColUp*(nCol+mxSample)
#endif
  ;
  db = sqlite3_context_db_handle(context);
  p = sqlite3DbMallocZero(db, n);
  if( p==0 ){
    sqlite3_result_error_nomem(context);
    return;
  }

  p->db = db;
  p->nRow = 0;
  p->nCol = nCol;
  p->nKeyCol = nKeyCol;
  p->current.anDLt = (tRowcnt*)&p[1];
  p->current.anEq = &p->current.anDLt[nColUp];

#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
  {
    u8 *pSpace;                     /* Allocated space not yet assigned */
    int i;                          /* Used to iterate through p->aSample[] */

    p->iGet = -1;
    p->mxSample = mxSample;
    p->nPSample = (tRowcnt)(sqlite3_value_int64(argv[2])/(mxSample/3+1) + 1);
    p->current.anLt = &p->current.anEq[nColUp];
    p->iPrn = 0x689e962d*(u32)nCol ^ 0xd0944565*(u32)sqlite3_value_int(argv[2]);

    /* Set up the Stat4Accum.a[] and aBest[] arrays */
    p->a = (struct Stat4Sample*)&p->current.anLt[nColUp];
    p->aBest = &p->a[mxSample];
    pSpace = (u8*)(&p->a[mxSample+nCol]);
    for(i=0; i<(mxSample+nCol); i++){
      p->a[i].anEq = (tRowcnt *)pSpace; pSpace += (sizeof(tRowcnt) * nColUp);
      p->a[i].anLt = (tRowcnt *)pSpace; pSpace += (sizeof(tRowcnt) * nColUp);
      p->a[i].anDLt = (tRowcnt *)pSpace; pSpace += (sizeof(tRowcnt) * nColUp);
    }
    assert( (pSpace - (u8*)p)==n );

    for(i=0; i<nCol; i++){
      p->aBest[i].iCol = i;
    }
  }
#endif

  /* Return a pointer to the allocated object to the caller.  Note that
  ** only the pointer (the 2nd parameter) matters.  The size of the object
  ** (given by the 3rd parameter) is never used and can be any positive
  ** value. */
  sqlite3_result_blob(context, p, sizeof(*p), stat4Destructor);
}