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
struct TYPE_5__ {scalar_t__ isInit; TYPE_1__* pBt; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ MemPage ;
typedef  int /*<<< orphan*/  DbPage ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  btreeInitPage (TYPE_2__*) ; 
 scalar_t__ sqlite3PagerGetExtra (int /*<<< orphan*/ *) ; 
 int sqlite3PagerPageRefcount (int /*<<< orphan*/ *) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pageReinit(DbPage *pData){
  MemPage *pPage;
  pPage = (MemPage *)sqlite3PagerGetExtra(pData);
  assert( sqlite3PagerPageRefcount(pData)>0 );
  if( pPage->isInit ){
    assert( sqlite3_mutex_held(pPage->pBt->mutex) );
    pPage->isInit = 0;
    if( sqlite3PagerPageRefcount(pData)>1 ){
      /* pPage might not be a btree page;  it might be an overflow page
      ** or ptrmap page or a free page.  In those cases, the following
      ** call to btreeInitPage() will likely return SQLITE_CORRUPT.
      ** But no harm is done by this.  And it is very important that
      ** btreeInitPage() be called on every btree page so we make
      ** the call for every page that comes in for re-initing. */
      btreeInitPage(pPage);
    }
  }
}