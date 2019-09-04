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
struct ReusableSpace {void* pSpace; int nFree; int nNeeded; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIGHT_BYTE_ALIGNMENT (void*) ; 
 int ROUND8 (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *allocSpace(
  struct ReusableSpace *p,  /* Bulk memory available for allocation */
  void *pBuf,               /* Pointer to a prior allocation */
  int nByte                 /* Bytes of memory needed */
){
  assert( EIGHT_BYTE_ALIGNMENT(p->pSpace) );
  if( pBuf==0 ){
    nByte = ROUND8(nByte);
    if( nByte <= p->nFree ){
      p->nFree -= nByte;
      pBuf = &p->pSpace[p->nFree];
    }else{
      p->nNeeded += nByte;
    }
  }
  assert( EIGHT_BYTE_ALIGNMENT(pBuf) );
  return pBuf;
}