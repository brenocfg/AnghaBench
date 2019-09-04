#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int wctrlFlags; scalar_t__ iLimit; } ;
typedef  TYPE_1__ WhereInfo ;
typedef  scalar_t__ LogEst ;

/* Variables and functions */
 int WHERE_USE_LIMIT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ estLog (scalar_t__) ; 
 int sqlite3LogEst (int) ; 

__attribute__((used)) static LogEst whereSortingCost(
  WhereInfo *pWInfo,
  LogEst nRow,
  int nOrderBy,
  int nSorted
){
  /* TUNING: Estimated cost of a full external sort, where N is
  ** the number of rows to sort is:
  **
  **   cost = (3.0 * N * log(N)).
  **
  ** Or, if the order-by clause has X terms but only the last Y
  ** terms are out of order, then block-sorting will reduce the
  ** sorting cost to:
  **
  **   cost = (3.0 * N * log(N)) * (Y/X)
  **
  ** The (Y/X) term is implemented using stack variable rScale
  ** below.  */
  LogEst rScale, rSortCost;
  assert( nOrderBy>0 && 66==sqlite3LogEst(100) );
  rScale = sqlite3LogEst((nOrderBy-nSorted)*100/nOrderBy) - 66;
  rSortCost = nRow + rScale + 16;

  /* Multiple by log(M) where M is the number of output rows.
  ** Use the LIMIT for M if it is smaller */
  if( (pWInfo->wctrlFlags & WHERE_USE_LIMIT)!=0 && pWInfo->iLimit<nRow ){
    nRow = pWInfo->iLimit;
  }
  rSortCost += estLog(nRow);
  return rSortCost;
}