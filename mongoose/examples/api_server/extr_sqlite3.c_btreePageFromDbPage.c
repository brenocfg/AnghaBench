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
struct TYPE_3__ {int pgno; int hdrOffset; int /*<<< orphan*/ * pBt; int /*<<< orphan*/ * pDbPage; int /*<<< orphan*/  aData; } ;
typedef  int Pgno ;
typedef  TYPE_1__ MemPage ;
typedef  int /*<<< orphan*/  DbPage ;
typedef  int /*<<< orphan*/  BtShared ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3PagerGetData (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3PagerGetExtra (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MemPage *btreePageFromDbPage(DbPage *pDbPage, Pgno pgno, BtShared *pBt){
  MemPage *pPage = (MemPage*)sqlite3PagerGetExtra(pDbPage);
  pPage->aData = sqlite3PagerGetData(pDbPage);
  pPage->pDbPage = pDbPage;
  pPage->pBt = pBt;
  pPage->pgno = pgno;
  pPage->hdrOffset = pPage->pgno==1 ? 100 : 0;
  return pPage; 
}