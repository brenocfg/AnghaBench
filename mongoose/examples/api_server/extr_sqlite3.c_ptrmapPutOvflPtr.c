#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {scalar_t__ nData; scalar_t__ nKey; scalar_t__ nPayload; int iOverflow; } ;
struct TYPE_6__ {int /*<<< orphan*/  pgno; int /*<<< orphan*/  pBt; scalar_t__ intKey; } ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  TYPE_1__ MemPage ;
typedef  TYPE_2__ CellInfo ;

/* Variables and functions */
 int /*<<< orphan*/  PTRMAP_OVERFLOW1 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  btreeParseCellPtr (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  get4byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptrmapPut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void ptrmapPutOvflPtr(MemPage *pPage, u8 *pCell, int *pRC){
  CellInfo info;
  if( *pRC ) return;
  assert( pCell!=0 );
  btreeParseCellPtr(pPage, pCell, &info);
  assert( (info.nData+(pPage->intKey?0:info.nKey))==info.nPayload );
  if( info.iOverflow ){
    Pgno ovfl = get4byte(&pCell[info.iOverflow]);
    ptrmapPut(pPage->pBt, ovfl, PTRMAP_OVERFLOW1, pPage->pgno, pRC);
  }
}