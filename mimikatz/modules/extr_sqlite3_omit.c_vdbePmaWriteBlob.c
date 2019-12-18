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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ eFWErr; int nBuffer; int iBufEnd; size_t iBufStart; scalar_t__ iWriteOff; int /*<<< orphan*/ * aBuffer; int /*<<< orphan*/  pFd; } ;
typedef  TYPE_1__ PmaWriter ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3OsWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void vdbePmaWriteBlob(PmaWriter *p, u8 *pData, int nData){
  int nRem = nData;
  while( nRem>0 && p->eFWErr==0 ){
    int nCopy = nRem;
    if( nCopy>(p->nBuffer - p->iBufEnd) ){
      nCopy = p->nBuffer - p->iBufEnd;
    }

    memcpy(&p->aBuffer[p->iBufEnd], &pData[nData-nRem], nCopy);
    p->iBufEnd += nCopy;
    if( p->iBufEnd==p->nBuffer ){
      p->eFWErr = sqlite3OsWrite(p->pFd, 
          &p->aBuffer[p->iBufStart], p->iBufEnd - p->iBufStart, 
          p->iWriteOff + p->iBufStart
      );
      p->iBufStart = p->iBufEnd = 0;
      p->iWriteOff += p->nBuffer;
    }
    assert( p->iBufEnd<p->nBuffer );

    nRem -= nCopy;
  }
}