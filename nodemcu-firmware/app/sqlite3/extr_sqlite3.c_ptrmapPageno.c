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
struct TYPE_4__ {int usableSize; int /*<<< orphan*/  mutex; } ;
typedef  int Pgno ;
typedef  TYPE_1__ BtShared ;

/* Variables and functions */
 int PENDING_BYTE_PAGE (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Pgno ptrmapPageno(BtShared *pBt, Pgno pgno){
  int nPagesPerMapPage;
  Pgno iPtrMap, ret;
  assert( sqlite3_mutex_held(pBt->mutex) );
  if( pgno<2 ) return 0;
  nPagesPerMapPage = (pBt->usableSize/5)+1;
  iPtrMap = (pgno-2)/nPagesPerMapPage;
  ret = (iPtrMap*nPagesPerMapPage) + 2;
  if( ret==PENDING_BYTE_PAGE(pBt) ){
    ret++;
  }
  return ret;
}