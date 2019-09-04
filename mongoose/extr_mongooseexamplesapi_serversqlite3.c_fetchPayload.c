#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {scalar_t__ nSize; unsigned char* pCell; int nLocal; scalar_t__ nKey; int /*<<< orphan*/  nHeader; } ;
struct TYPE_8__ {size_t iPage; scalar_t__ eState; scalar_t__* aiIdx; TYPE_6__ info; TYPE_1__** apPage; } ;
struct TYPE_7__ {scalar_t__ nCell; scalar_t__ intKey; } ;
typedef  TYPE_1__ MemPage ;
typedef  TYPE_2__ BtCursor ;

/* Variables and functions */
 scalar_t__ CURSOR_VALID ; 
 scalar_t__ NEVER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  btreeParseCell (TYPE_1__*,scalar_t__,TYPE_6__*) ; 
 int cursorHoldsMutex (TYPE_2__*) ; 

__attribute__((used)) static const unsigned char *fetchPayload(
  BtCursor *pCur,      /* Cursor pointing to entry to read from */
  int *pAmt,           /* Write the number of available bytes here */
  int skipKey          /* read beginning at data if this is true */
){
  unsigned char *aPayload;
  MemPage *pPage;
  u32 nKey;
  u32 nLocal;

  assert( pCur!=0 && pCur->iPage>=0 && pCur->apPage[pCur->iPage]);
  assert( pCur->eState==CURSOR_VALID );
  assert( cursorHoldsMutex(pCur) );
  pPage = pCur->apPage[pCur->iPage];
  assert( pCur->aiIdx[pCur->iPage]<pPage->nCell );
  if( NEVER(pCur->info.nSize==0) ){
    btreeParseCell(pCur->apPage[pCur->iPage], pCur->aiIdx[pCur->iPage],
                   &pCur->info);
  }
  aPayload = pCur->info.pCell;
  aPayload += pCur->info.nHeader;
  if( pPage->intKey ){
    nKey = 0;
  }else{
    nKey = (int)pCur->info.nKey;
  }
  if( skipKey ){
    aPayload += nKey;
    nLocal = pCur->info.nLocal - nKey;
  }else{
    nLocal = pCur->info.nLocal;
    assert( nLocal<=nKey );
  }
  *pAmt = nLocal;
  return aPayload;
}