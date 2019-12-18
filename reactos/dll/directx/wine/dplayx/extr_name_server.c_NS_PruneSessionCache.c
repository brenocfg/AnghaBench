#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* lpNSCacheData ;
typedef  TYPE_2__* lpNSCache ;
struct TYPE_9__ {int /*<<< orphan*/  first; } ;
struct TYPE_8__ {scalar_t__ const dwTime; } ;
typedef  TYPE_2__* LPVOID ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ DPMSG_WAIT_60_SECS ; 
 TYPE_1__* DPQ_FIRST (int /*<<< orphan*/ ) ; 
 scalar_t__ DPQ_IS_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPQ_REMOVE (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbDeleteNSNodeFromHeap (TYPE_1__*) ; 
 int /*<<< orphan*/  next ; 
 scalar_t__ timeGetTime () ; 

void NS_PruneSessionCache( LPVOID lpNSInfo )
{
  lpNSCache     lpCache = lpNSInfo;

  const DWORD dwPresentTime = timeGetTime();
  const DWORD dwPrunePeriod = DPMSG_WAIT_60_SECS; /* is 60 secs enough? */

  /* This silly little algorithm is based on the fact we keep entries in
   * the queue in a time based order. It also assumes that it is not possible
   * to wrap around over yourself (which is not unreasonable).
   * The if statements verify if the first entry in the queue is less
   * than dwPrunePeriod old depending on the "clock" roll over.
   */
  for( ;; )
  {
    lpNSCacheData lpFirstData;

    if( DPQ_IS_EMPTY(lpCache->first) )
    {
      /* Nothing to prune */
      break;
    }

    /* Deal with time in a wrap around safe manner - unsigned arithmetic.
     * Check the difference in time */
    if( (dwPresentTime - (DPQ_FIRST(lpCache->first)->dwTime)) < dwPrunePeriod )
    {
      /* First entry has not expired yet; don't prune */
      break;
    }

    lpFirstData = DPQ_FIRST(lpCache->first);
    DPQ_REMOVE( lpCache->first, DPQ_FIRST(lpCache->first), next );
    cbDeleteNSNodeFromHeap( lpFirstData );
  }

}