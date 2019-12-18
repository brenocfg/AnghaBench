#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UnpackedRecord ;
struct TYPE_5__ {TYPE_1__* pSorter; int /*<<< orphan*/ * pUnpacked; } ;
struct TYPE_4__ {int /*<<< orphan*/  pKeyInfo; } ;
typedef  TYPE_2__ SortSubtask ;

/* Variables and functions */
 int sqlite3VdbeRecordCompareWithSkip (int,void const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeRecordUnpack (int /*<<< orphan*/ ,int,void const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vdbeSorterCompareTail(
  SortSubtask *pTask,             /* Subtask context (for pKeyInfo) */
  int *pbKey2Cached,              /* True if pTask->pUnpacked is pKey2 */
  const void *pKey1, int nKey1,   /* Left side of comparison */
  const void *pKey2, int nKey2    /* Right side of comparison */
){
  UnpackedRecord *r2 = pTask->pUnpacked;
  if( *pbKey2Cached==0 ){
    sqlite3VdbeRecordUnpack(pTask->pSorter->pKeyInfo, nKey2, pKey2, r2);
    *pbKey2Cached = 1;
  }
  return sqlite3VdbeRecordCompareWithSkip(nKey1, pKey1, r2, 1);
}