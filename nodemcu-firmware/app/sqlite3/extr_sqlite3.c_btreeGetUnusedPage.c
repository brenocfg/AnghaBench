#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ isInit; int /*<<< orphan*/  pDbPage; } ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  TYPE_1__ MemPage ;
typedef  int /*<<< orphan*/  BtShared ;

/* Variables and functions */
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 int btreeGetPage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**,int) ; 
 int /*<<< orphan*/  releasePage (TYPE_1__*) ; 
 int sqlite3PagerPageRefcount (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btreeGetUnusedPage(
  BtShared *pBt,       /* The btree */
  Pgno pgno,           /* Number of the page to fetch */
  MemPage **ppPage,    /* Return the page in this parameter */
  int flags            /* PAGER_GET_NOCONTENT or PAGER_GET_READONLY */
){
  int rc = btreeGetPage(pBt, pgno, ppPage, flags);
  if( rc==SQLITE_OK ){
    if( sqlite3PagerPageRefcount((*ppPage)->pDbPage)>1 ){
      releasePage(*ppPage);
      *ppPage = 0;
      return SQLITE_CORRUPT_BKPT;
    }
    (*ppPage)->isInit = 0;
  }else{
    *ppPage = 0;
  }
  return rc;
}