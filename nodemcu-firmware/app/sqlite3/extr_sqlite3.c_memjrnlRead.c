#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ sqlite_int64 ;
typedef  scalar_t__ sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_9__ {scalar_t__ zChunk; struct TYPE_9__* pNext; } ;
struct TYPE_7__ {scalar_t__ iOffset; TYPE_4__* pChunk; } ;
struct TYPE_6__ {scalar_t__ iOffset; } ;
struct TYPE_8__ {scalar_t__ nChunkSize; TYPE_2__ readpoint; TYPE_4__* pFirst; TYPE_1__ endpoint; } ;
typedef  TYPE_3__ MemJournal ;
typedef  TYPE_4__ FileChunk ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_4__*) ; 
 int MIN (int,int) ; 
 int SQLITE_IOERR_SHORT_READ ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int memjrnlRead(
  sqlite3_file *pJfd,    /* The journal file from which to read */
  void *zBuf,            /* Put the results here */
  int iAmt,              /* Number of bytes to read */
  sqlite_int64 iOfst     /* Begin reading at this offset */
){
  MemJournal *p = (MemJournal *)pJfd;
  u8 *zOut = zBuf;
  int nRead = iAmt;
  int iChunkOffset;
  FileChunk *pChunk;

#ifdef SQLITE_ENABLE_ATOMIC_WRITE
  if( (iAmt+iOfst)>p->endpoint.iOffset ){
    return SQLITE_IOERR_SHORT_READ;
  }
#endif

  assert( (iAmt+iOfst)<=p->endpoint.iOffset );
  assert( p->readpoint.iOffset==0 || p->readpoint.pChunk!=0 );
  if( p->readpoint.iOffset!=iOfst || iOfst==0 ){
    sqlite3_int64 iOff = 0;
    for(pChunk=p->pFirst;
        ALWAYS(pChunk) && (iOff+p->nChunkSize)<=iOfst;
        pChunk=pChunk->pNext
    ){
      iOff += p->nChunkSize;
    }
  }else{
    pChunk = p->readpoint.pChunk;
    assert( pChunk!=0 );
  }

  iChunkOffset = (int)(iOfst%p->nChunkSize);
  do {
    int iSpace = p->nChunkSize - iChunkOffset;
    int nCopy = MIN(nRead, (p->nChunkSize - iChunkOffset));
    memcpy(zOut, (u8*)pChunk->zChunk + iChunkOffset, nCopy);
    zOut += nCopy;
    nRead -= iSpace;
    iChunkOffset = 0;
  } while( nRead>=0 && (pChunk=pChunk->pNext)!=0 && nRead>0 );
  p->readpoint.iOffset = pChunk ? iOfst+iAmt : 0;
  p->readpoint.pChunk = pChunk;

  return SQLITE_OK;
}