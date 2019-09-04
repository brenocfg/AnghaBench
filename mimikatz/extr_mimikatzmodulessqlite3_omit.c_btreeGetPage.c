#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pPager; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  int /*<<< orphan*/  MemPage ;
typedef  int /*<<< orphan*/  DbPage ;
typedef  TYPE_1__ BtShared ;

/* Variables and functions */
 int PAGER_GET_NOCONTENT ; 
 int PAGER_GET_READONLY ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * btreePageFromDbPage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sqlite3PagerGet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btreeGetPage(
  BtShared *pBt,       /* The btree */
  Pgno pgno,           /* Number of the page to fetch */
  MemPage **ppPage,    /* Return the page in this parameter */
  int flags            /* PAGER_GET_NOCONTENT or PAGER_GET_READONLY */
){
  int rc;
  DbPage *pDbPage;

  assert( flags==0 || flags==PAGER_GET_NOCONTENT || flags==PAGER_GET_READONLY );
  assert( sqlite3_mutex_held(pBt->mutex) );
  rc = sqlite3PagerGet(pBt->pPager, pgno, (DbPage**)&pDbPage, flags);
  if( rc ) return rc;
  *ppPage = btreePageFromDbPage(pDbPage, pgno, pBt);
  return SQLITE_OK;
}