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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  ht_slot ;
struct TYPE_3__ {int /*<<< orphan*/ * aPgno; scalar_t__ iZero; int /*<<< orphan*/  volatile* aHash; } ;
typedef  TYPE_1__ WalHashLoc ;
typedef  int /*<<< orphan*/  Wal ;

/* Variables and functions */
 size_t HASHTABLE_NPAGE ; 
 scalar_t__ HASHTABLE_NPAGE_ONE ; 
 int SQLITE_OK ; 
 int WALINDEX_HDR_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int walIndexPage (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int walHashGet(
  Wal *pWal,                      /* WAL handle */
  int iHash,                      /* Find the iHash'th table */
  WalHashLoc *pLoc                /* OUT: Hash table location */
){
  int rc;                         /* Return code */

  rc = walIndexPage(pWal, iHash, &pLoc->aPgno);
  assert( rc==SQLITE_OK || iHash>0 );

  if( rc==SQLITE_OK ){
    pLoc->aHash = (volatile ht_slot *)&pLoc->aPgno[HASHTABLE_NPAGE];
    if( iHash==0 ){
      pLoc->aPgno = &pLoc->aPgno[WALINDEX_HDR_SIZE/sizeof(u32)];
      pLoc->iZero = 0;
    }else{
      pLoc->iZero = HASHTABLE_NPAGE_ONE + (iHash-1)*HASHTABLE_NPAGE;
    }
    pLoc->aPgno = &pLoc->aPgno[-1];
  }
  return rc;
}