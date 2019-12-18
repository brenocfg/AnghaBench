#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  ht_slot ;
typedef  int /*<<< orphan*/  Wal ;

/* Variables and functions */
 size_t HASHTABLE_NPAGE ; 
 scalar_t__ HASHTABLE_NPAGE_ONE ; 
 int SQLITE_OK ; 
 int WALINDEX_HDR_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int walIndexPage (int /*<<< orphan*/ *,int,scalar_t__ volatile**) ; 

__attribute__((used)) static int walHashGet(
  Wal *pWal,                      /* WAL handle */
  int iHash,                      /* Find the iHash'th table */
  volatile ht_slot **paHash,      /* OUT: Pointer to hash index */
  volatile u32 **paPgno,          /* OUT: Pointer to page number array */
  u32 *piZero                     /* OUT: Frame associated with *paPgno[0] */
){
  int rc;                         /* Return code */
  volatile u32 *aPgno;

  rc = walIndexPage(pWal, iHash, &aPgno);
  assert( rc==SQLITE_OK || iHash>0 );

  if( rc==SQLITE_OK ){
    u32 iZero;
    volatile ht_slot *aHash;

    aHash = (volatile ht_slot *)&aPgno[HASHTABLE_NPAGE];
    if( iHash==0 ){
      aPgno = &aPgno[WALINDEX_HDR_SIZE/sizeof(u32)];
      iZero = 0;
    }else{
      iZero = HASHTABLE_NPAGE_ONE + (iHash-1)*HASHTABLE_NPAGE;
    }

    *paPgno = &aPgno[-1];
    *paHash = aHash;
    *piZero = iZero;
  }
  return rc;
}