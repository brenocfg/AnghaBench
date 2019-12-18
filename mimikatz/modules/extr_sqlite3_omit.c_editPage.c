#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_17__ {int /*<<< orphan*/  (* xCellSize ) (TYPE_4__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_16__ {int /*<<< orphan*/ ** apCell; TYPE_4__* pRef; } ;
struct TYPE_15__ {int hdrOffset; int nCell; int nOverflow; int* aiOvfl; TYPE_1__* pBt; int /*<<< orphan*/ * aCellIdx; int /*<<< orphan*/ * aData; } ;
struct TYPE_14__ {size_t usableSize; int /*<<< orphan*/  pPager; } ;
typedef  TYPE_2__ MemPage ;
typedef  TYPE_3__ CellArray ;

/* Variables and functions */
 scalar_t__ CORRUPT_DB ; 
 int MIN (int,int) ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_WITHIN (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int get2byteAligned (int /*<<< orphan*/ *) ; 
 size_t get2byteNotZero (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,size_t) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pageFreeArray (TYPE_2__*,int,int,TYPE_3__*) ; 
 scalar_t__ pageInsertArray (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int,TYPE_3__*) ; 
 int /*<<< orphan*/  populateCellCache (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  put2byte (int /*<<< orphan*/ *,int) ; 
 int rebuildPage (TYPE_3__*,int,int,TYPE_2__*) ; 
 int /*<<< orphan*/ * sqlite3PagerTempSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int editPage(
  MemPage *pPg,                   /* Edit this page */
  int iOld,                       /* Index of first cell currently on page */
  int iNew,                       /* Index of new first cell on page */
  int nNew,                       /* Final number of cells on page */
  CellArray *pCArray              /* Array of cells and sizes */
){
  u8 * const aData = pPg->aData;
  const int hdr = pPg->hdrOffset;
  u8 *pBegin = &pPg->aCellIdx[nNew * 2];
  int nCell = pPg->nCell;       /* Cells stored on pPg */
  u8 *pData;
  u8 *pCellptr;
  int i;
  int iOldEnd = iOld + pPg->nCell + pPg->nOverflow;
  int iNewEnd = iNew + nNew;

#ifdef SQLITE_DEBUG
  u8 *pTmp = sqlite3PagerTempSpace(pPg->pBt->pPager);
  memcpy(pTmp, aData, pPg->pBt->usableSize);
#endif

  /* Remove cells from the start and end of the page */
  assert( nCell>=0 );
  if( iOld<iNew ){
    int nShift = pageFreeArray(pPg, iOld, iNew-iOld, pCArray);
    if( nShift>nCell ) return SQLITE_CORRUPT_BKPT;
    memmove(pPg->aCellIdx, &pPg->aCellIdx[nShift*2], nCell*2);
    nCell -= nShift;
  }
  if( iNewEnd < iOldEnd ){
    int nTail = pageFreeArray(pPg, iNewEnd, iOldEnd - iNewEnd, pCArray);
    assert( nCell>=nTail );
    nCell -= nTail;
  }

  pData = &aData[get2byteNotZero(&aData[hdr+5])];
  if( pData<pBegin ) goto editpage_fail;

  /* Add cells to the start of the page */
  if( iNew<iOld ){
    int nAdd = MIN(nNew,iOld-iNew);
    assert( (iOld-iNew)<nNew || nCell==0 || CORRUPT_DB );
    assert( nAdd>=0 );
    pCellptr = pPg->aCellIdx;
    memmove(&pCellptr[nAdd*2], pCellptr, nCell*2);
    if( pageInsertArray(
          pPg, pBegin, &pData, pCellptr,
          iNew, nAdd, pCArray
    ) ) goto editpage_fail;
    nCell += nAdd;
  }

  /* Add any overflow cells */
  for(i=0; i<pPg->nOverflow; i++){
    int iCell = (iOld + pPg->aiOvfl[i]) - iNew;
    if( iCell>=0 && iCell<nNew ){
      pCellptr = &pPg->aCellIdx[iCell * 2];
      assert( nCell>=iCell );
      memmove(&pCellptr[2], pCellptr, (nCell - iCell) * 2);
      nCell++;
      if( pageInsertArray(
            pPg, pBegin, &pData, pCellptr,
            iCell+iNew, 1, pCArray
      ) ) goto editpage_fail;
    }
  }

  /* Append cells to the end of the page */
  assert( nCell>=0 );
  pCellptr = &pPg->aCellIdx[nCell*2];
  if( pageInsertArray(
        pPg, pBegin, &pData, pCellptr,
        iNew+nCell, nNew-nCell, pCArray
  ) ) goto editpage_fail;

  pPg->nCell = nNew;
  pPg->nOverflow = 0;

  put2byte(&aData[hdr+3], pPg->nCell);
  put2byte(&aData[hdr+5], pData - aData);

#ifdef SQLITE_DEBUG
  for(i=0; i<nNew && !CORRUPT_DB; i++){
    u8 *pCell = pCArray->apCell[i+iNew];
    int iOff = get2byteAligned(&pPg->aCellIdx[i*2]);
    if( SQLITE_WITHIN(pCell, aData, &aData[pPg->pBt->usableSize]) ){
      pCell = &pTmp[pCell - aData];
    }
    assert( 0==memcmp(pCell, &aData[iOff],
            pCArray->pRef->xCellSize(pCArray->pRef, pCArray->apCell[i+iNew])) );
  }
#endif

  return SQLITE_OK;
 editpage_fail:
  /* Unable to edit this page. Rebuild it from scratch instead. */
  populateCellCache(pCArray, iNew, nNew);
  return rebuildPage(pCArray, iNew, nNew, pPg);
}